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
struct kobject {int /*<<< orphan*/  sd; } ;
struct attribute {int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kobject_get_ownership (struct kobject*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sysfs_add_file_mode_ns (int /*<<< orphan*/ ,struct attribute const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 

int sysfs_create_file_ns(struct kobject *kobj, const struct attribute *attr,
			 const void *ns)
{
	kuid_t uid;
	kgid_t gid;

	if (WARN_ON(!kobj || !kobj->sd || !attr))
		return -EINVAL;

	kobject_get_ownership(kobj, &uid, &gid);
	return sysfs_add_file_mode_ns(kobj->sd, attr, false, attr->mode,
				      uid, gid, ns);

}