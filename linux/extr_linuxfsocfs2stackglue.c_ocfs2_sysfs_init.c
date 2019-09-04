#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  fs_kobj ; 
 TYPE_1__* kset_create_and_add (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kset_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  ocfs2_attr_group ; 
 TYPE_1__* ocfs2_kset ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_sysfs_init(void)
{
	int ret;

	ocfs2_kset = kset_create_and_add("ocfs2", NULL, fs_kobj);
	if (!ocfs2_kset)
		return -ENOMEM;

	ret = sysfs_create_group(&ocfs2_kset->kobj, &ocfs2_attr_group);
	if (ret)
		goto error;

	return 0;

error:
	kset_unregister(ocfs2_kset);
	return ret;
}