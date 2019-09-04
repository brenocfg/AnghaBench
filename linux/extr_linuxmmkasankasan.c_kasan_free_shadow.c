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
struct vm_struct {int flags; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int VM_KASAN ; 
 int /*<<< orphan*/  kasan_mem_to_shadow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void kasan_free_shadow(const struct vm_struct *vm)
{
	if (vm->flags & VM_KASAN)
		vfree(kasan_mem_to_shadow(vm->addr));
}