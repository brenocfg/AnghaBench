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
struct xfs_kobj {int /*<<< orphan*/  complete; } ;
struct kobject {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct xfs_kobj* to_kobj (struct kobject*) ; 

__attribute__((used)) static inline void
xfs_sysfs_release(struct kobject *kobject)
{
	struct xfs_kobj *kobj = to_kobj(kobject);
	complete(&kobj->complete);
}