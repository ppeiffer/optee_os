/*
 * Copyright (c) 2015, Linaro Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef KERNEL_GENERIC_BOOT_H
#define KERNEL_GENERIC_BOOT_H

#include <initcall.h>
#include <types_ext.h>

#if defined(CFG_WITH_ARM_TRUSTED_FW)
unsigned long cpu_on_handler(unsigned long a0, unsigned long a1);
struct thread_vector_table *
generic_boot_init_primary(unsigned long pageable_part, unsigned long unused,
			  unsigned long fdt);
unsigned long generic_boot_cpu_on_handler(unsigned long a0, unsigned long a1);
#else
void generic_boot_init_primary(unsigned long pageable_part,
			       unsigned long nsec_entry, unsigned long fdt);
void generic_boot_init_secondary(unsigned long nsec_entry);
#endif

void main_init_gic(void);
void main_secondary_init_gic(void);

void init_sec_mon(unsigned long nsec_entry);

const struct thread_handlers *generic_boot_get_handlers(void);

/* weak routines eventually overridden by platform */
void plat_cpu_reset_early(void);
void plat_cpu_reset_late(void);
void arm_cl2_config(vaddr_t pl310);
void arm_cl2_enable(vaddr_t pl310);

#if defined(CFG_BOOT_SECONDARY_REQUEST)
extern paddr_t ns_entry_addrs[] __early_bss;
int generic_boot_core_release(size_t core_idx, paddr_t entry);
paddr_t generic_boot_core_hpen(void);
#endif

#define VCORE_UNPG_RX_PA	((paddr_t)__vcore_unpg_rx_start)
#define VCORE_UNPG_RX_SZ	((size_t)__vcore_unpg_rx_size)
#define VCORE_UNPG_RO_PA	((paddr_t)__vcore_unpg_ro_start)
#define VCORE_UNPG_RO_SZ	((size_t)__vcore_unpg_ro_size)
#define VCORE_UNPG_RW_PA	((paddr_t)__vcore_unpg_rw_start)
#define VCORE_UNPG_RW_SZ	((size_t)__vcore_unpg_rw_size)
#define VCORE_INIT_RX_PA	((paddr_t)__vcore_init_rx_start)
#define VCORE_INIT_RX_SZ	((size_t)__vcore_init_rx_size)
#define VCORE_INIT_RO_PA	((paddr_t)__vcore_init_ro_start)
#define VCORE_INIT_RO_SZ	((size_t)__vcore_init_ro_size)

extern uint8_t __vcore_unpg_rx_start[];
extern uint8_t __vcore_unpg_rx_size[];
extern uint8_t __vcore_unpg_ro_start[];
extern uint8_t __vcore_unpg_ro_size[];
extern uint8_t __vcore_unpg_rw_start[];
extern uint8_t __vcore_unpg_rw_size[];
extern uint8_t __vcore_init_rx_start[];
extern uint8_t __vcore_init_rx_size[];
extern uint8_t __vcore_init_ro_start[];
extern uint8_t __vcore_init_ro_size[];

extern uint8_t __text_start[];
extern initcall_t __initcall_start;
extern initcall_t __initcall_end;
extern uint8_t __data_start[];
extern uint8_t __data_end[];
extern uint8_t __rodata_start[];
extern uint8_t __rodata_end[];
extern uint8_t __early_bss_start[];
extern uint8_t __early_bss_end[];
extern uint8_t __bss_start[];
extern uint8_t __bss_end[];
extern uint8_t __nozi_start[];
extern uint8_t __nozi_end[];
extern uint8_t __nozi_stack_start[];
extern uint8_t __nozi_stack_end[];
extern uint8_t __init_start[];
extern uint8_t __init_size[];
extern uint8_t __tmp_hashes_start[];
extern uint8_t __tmp_hashes_size[];
extern uint8_t __heap1_start[];
extern uint8_t __heap1_end[];
extern uint8_t __heap2_start[];
extern uint8_t __heap2_end[];
extern uint8_t __pageable_part_start[];
extern uint8_t __pageable_part_end[];
extern uint8_t __pageable_start[];
extern uint8_t __pageable_end[];
extern uint8_t __asan_shadow_start[];
extern uint8_t __asan_shadow_end[];
extern vaddr_t __ctor_list;
extern vaddr_t __ctor_end;
extern uint8_t __end[];

/* Generated by core/arch/arm/kernel/link.mk */
extern const char core_v_str[];

#endif /* KERNEL_GENERIC_BOOT_H */
