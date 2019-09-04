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
struct vfio_group {scalar_t__ kvm; int /*<<< orphan*/  notifier; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long VFIO_GROUP_NOTIFY_SET_KVM ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,unsigned long,scalar_t__) ; 
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int vfio_group_add_container_user (struct vfio_group*) ; 
 int /*<<< orphan*/  vfio_group_try_dissolve_container (struct vfio_group*) ; 

__attribute__((used)) static int vfio_register_group_notifier(struct vfio_group *group,
					unsigned long *events,
					struct notifier_block *nb)
{
	int ret;
	bool set_kvm = false;

	if (*events & VFIO_GROUP_NOTIFY_SET_KVM)
		set_kvm = true;

	/* clear known events */
	*events &= ~VFIO_GROUP_NOTIFY_SET_KVM;

	/* refuse to continue if still events remaining */
	if (*events)
		return -EINVAL;

	ret = vfio_group_add_container_user(group);
	if (ret)
		return -EINVAL;

	ret = blocking_notifier_chain_register(&group->notifier, nb);

	/*
	 * The attaching of kvm and vfio_group might already happen, so
	 * here we replay once upon registration.
	 */
	if (!ret && set_kvm && group->kvm)
		blocking_notifier_call_chain(&group->notifier,
					VFIO_GROUP_NOTIFY_SET_KVM, group->kvm);

	vfio_group_try_dissolve_container(group);

	return ret;
}