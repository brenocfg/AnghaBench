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
struct kvm_io_device {int dummy; } ;
struct kvm_coalesced_mmio_dev {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct kvm_coalesced_mmio_dev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct kvm_coalesced_mmio_dev* to_mmio (struct kvm_io_device*) ; 

__attribute__((used)) static void coalesced_mmio_destructor(struct kvm_io_device *this)
{
	struct kvm_coalesced_mmio_dev *dev = to_mmio(this);

	list_del(&dev->list);

	kfree(dev);
}