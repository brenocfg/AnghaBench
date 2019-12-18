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
struct vgic_its {int /*<<< orphan*/  its_lock; struct vgic_its* private; struct kvm* kvm; } ;
struct kvm_device {int /*<<< orphan*/  its_lock; struct kvm_device* private; struct kvm* kvm; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vgic_its*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_its_free_collection_list (struct kvm*,struct vgic_its*) ; 
 int /*<<< orphan*/  vgic_its_free_device_list (struct kvm*,struct vgic_its*) ; 

__attribute__((used)) static void vgic_its_destroy(struct kvm_device *kvm_dev)
{
	struct kvm *kvm = kvm_dev->kvm;
	struct vgic_its *its = kvm_dev->private;

	mutex_lock(&its->its_lock);

	vgic_its_free_device_list(kvm, its);
	vgic_its_free_collection_list(kvm, its);

	mutex_unlock(&its->its_lock);
	kfree(its);
	kfree(kvm_dev);/* alloc by kvm_ioctl_create_device, free by .destroy */
}