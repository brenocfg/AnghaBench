#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vcpu {TYPE_1__* state; } ;
struct kvm_vm {struct vcpu* vcpu_head; } ;
struct TYPE_2__ {int /*<<< orphan*/  psw_addr; int /*<<< orphan*/  psw_mask; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vcpu_dump(FILE *stream, struct kvm_vm *vm, uint32_t vcpuid, uint8_t indent)
{
	struct vcpu *vcpu = vm->vcpu_head;

	fprintf(stream, "%*spstate: psw: 0x%.16llx:0x%.16llx\n",
		indent, "", vcpu->state->psw_mask, vcpu->state->psw_addr);
}