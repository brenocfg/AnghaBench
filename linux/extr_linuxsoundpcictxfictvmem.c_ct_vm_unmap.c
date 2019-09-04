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
struct ct_vm_block {int dummy; } ;
struct ct_vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_vm_block (struct ct_vm*,struct ct_vm_block*) ; 

__attribute__((used)) static void ct_vm_unmap(struct ct_vm *vm, struct ct_vm_block *block)
{
	/* do unmapping */
	put_vm_block(vm, block);
}