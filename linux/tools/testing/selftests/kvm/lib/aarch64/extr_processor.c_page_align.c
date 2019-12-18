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
struct kvm_vm {int page_size; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t page_align(struct kvm_vm *vm, uint64_t v)
{
	return (v + vm->page_size) & ~(vm->page_size - 1);
}