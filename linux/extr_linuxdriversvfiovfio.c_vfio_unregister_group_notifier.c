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
struct vfio_group {int /*<<< orphan*/  notifier; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int blocking_notifier_chain_unregister (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int vfio_group_add_container_user (struct vfio_group*) ; 
 int /*<<< orphan*/  vfio_group_try_dissolve_container (struct vfio_group*) ; 

__attribute__((used)) static int vfio_unregister_group_notifier(struct vfio_group *group,
					 struct notifier_block *nb)
{
	int ret;

	ret = vfio_group_add_container_user(group);
	if (ret)
		return -EINVAL;

	ret = blocking_notifier_chain_unregister(&group->notifier, nb);

	vfio_group_try_dissolve_container(group);

	return ret;
}