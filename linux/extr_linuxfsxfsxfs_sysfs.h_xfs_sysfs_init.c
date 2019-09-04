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
struct xfs_kobj {int /*<<< orphan*/  kobject; int /*<<< orphan*/  complete; } ;
struct kobj_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,struct kobj_type*,int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static inline int
xfs_sysfs_init(
	struct xfs_kobj		*kobj,
	struct kobj_type	*ktype,
	struct xfs_kobj		*parent_kobj,
	const char		*name)
{
	init_completion(&kobj->complete);
	return kobject_init_and_add(&kobj->kobject, ktype,
				    &parent_kobj->kobject, "%s", name);
}