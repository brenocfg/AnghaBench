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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  fs_kobj ; 
 int /*<<< orphan*/  gfs2_kset ; 
 int /*<<< orphan*/  gfs2_uevent_ops ; 
 int /*<<< orphan*/  kset_create_and_add (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int gfs2_sys_init(void)
{
	gfs2_kset = kset_create_and_add("gfs2", &gfs2_uevent_ops, fs_kobj);
	if (!gfs2_kset)
		return -ENOMEM;
	return 0;
}