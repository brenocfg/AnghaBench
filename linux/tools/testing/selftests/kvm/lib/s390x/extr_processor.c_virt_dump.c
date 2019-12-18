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
typedef  int /*<<< orphan*/  uint8_t ;
struct kvm_vm {int /*<<< orphan*/  pgd; int /*<<< orphan*/  pgd_created; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  virt_dump_region (int /*<<< orphan*/ *,struct kvm_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void virt_dump(FILE *stream, struct kvm_vm *vm, uint8_t indent)
{
	if (!vm->pgd_created)
		return;

	virt_dump_region(stream, vm, indent, vm->pgd);
}