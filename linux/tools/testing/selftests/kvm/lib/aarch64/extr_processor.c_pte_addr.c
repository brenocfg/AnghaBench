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
struct kvm_vm {unsigned long va_bits; unsigned long page_shift; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t pte_addr(struct kvm_vm *vm, uint64_t entry)
{
	uint64_t mask = ((1UL << (vm->va_bits - vm->page_shift)) - 1) << vm->page_shift;
	return entry & mask;
}