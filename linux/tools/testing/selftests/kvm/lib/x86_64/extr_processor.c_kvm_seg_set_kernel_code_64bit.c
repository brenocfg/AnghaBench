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
typedef  int /*<<< orphan*/  uint16_t ;
struct kvm_vm {int dummy; } ;
struct kvm_segment {int limit; int s; int type; int g; int l; int present; int /*<<< orphan*/  selector; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_seg_fill_gdt_64bit (struct kvm_vm*,struct kvm_segment*) ; 
 int /*<<< orphan*/  memset (struct kvm_segment*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kvm_seg_set_kernel_code_64bit(struct kvm_vm *vm, uint16_t selector,
	struct kvm_segment *segp)
{
	memset(segp, 0, sizeof(*segp));
	segp->selector = selector;
	segp->limit = 0xFFFFFFFFu;
	segp->s = 0x1; /* kTypeCodeData */
	segp->type = 0x08 | 0x01 | 0x02; /* kFlagCode | kFlagCodeAccessed
					  * | kFlagCodeReadable
					  */
	segp->g = true;
	segp->l = true;
	segp->present = 1;
	if (vm)
		kvm_seg_fill_gdt_64bit(vm, segp);
}