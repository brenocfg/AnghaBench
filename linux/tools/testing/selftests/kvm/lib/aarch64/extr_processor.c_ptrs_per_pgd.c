#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
struct kvm_vm {int pgtable_levels; int page_shift; unsigned int va_bits; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t ptrs_per_pgd(struct kvm_vm *vm)
{
	unsigned int shift = (vm->pgtable_levels - 1) * (vm->page_shift - 3) + vm->page_shift;
	return 1 << (vm->va_bits - shift);
}