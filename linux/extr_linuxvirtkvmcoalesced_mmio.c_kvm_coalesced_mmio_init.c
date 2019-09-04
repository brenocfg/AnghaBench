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
struct page {int dummy; } ;
struct kvm {int /*<<< orphan*/  coalesced_zones; int /*<<< orphan*/  ring_lock; int /*<<< orphan*/  coalesced_mmio_ring; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int __GFP_ZERO ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int kvm_coalesced_mmio_init(struct kvm *kvm)
{
	struct page *page;
	int ret;

	ret = -ENOMEM;
	page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	if (!page)
		goto out_err;

	ret = 0;
	kvm->coalesced_mmio_ring = page_address(page);

	/*
	 * We're using this spinlock to sync access to the coalesced ring.
	 * The list doesn't need it's own lock since device registration and
	 * unregistration should only happen when kvm->slots_lock is held.
	 */
	spin_lock_init(&kvm->ring_lock);
	INIT_LIST_HEAD(&kvm->coalesced_zones);

out_err:
	return ret;
}