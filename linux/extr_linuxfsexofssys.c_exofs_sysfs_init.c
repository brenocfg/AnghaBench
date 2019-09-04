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
 int /*<<< orphan*/  EXOFS_ERR (char*) ; 
 int /*<<< orphan*/  exofs_kset ; 
 int /*<<< orphan*/  fs_kobj ; 
 int /*<<< orphan*/  kset_create_and_add (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int exofs_sysfs_init(void)
{
	exofs_kset = kset_create_and_add("exofs", NULL, fs_kobj);
	if (!exofs_kset) {
		EXOFS_ERR("ERROR: kset_create_and_add exofs failed\n");
		return -ENOMEM;
	}
	return 0;
}