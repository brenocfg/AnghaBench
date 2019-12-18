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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct kvm_vm {int /*<<< orphan*/  fd; } ;
struct kvm_clear_dirty_log {void* dirty_bitmap; int slot; int /*<<< orphan*/  num_pages; int /*<<< orphan*/  first_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_CLEAR_DIRTY_LOG ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int /*<<< orphan*/ ) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvm_clear_dirty_log*) ; 
 int /*<<< orphan*/  strerror (int) ; 

void kvm_vm_clear_dirty_log(struct kvm_vm *vm, int slot, void *log,
			    uint64_t first_page, uint32_t num_pages)
{
	struct kvm_clear_dirty_log args = { .dirty_bitmap = log, .slot = slot,
		                            .first_page = first_page,
	                                    .num_pages = num_pages };
	int ret;

	ret = ioctl(vm->fd, KVM_CLEAR_DIRTY_LOG, &args);
	TEST_ASSERT(ret == 0, "%s: KVM_CLEAR_DIRTY_LOG failed: %s",
		    strerror(-ret));
}