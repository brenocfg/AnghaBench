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
struct nilfs_root {int /*<<< orphan*/  snapshot_kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 

void nilfs_sysfs_delete_snapshot_group(struct nilfs_root *root)
{
	kobject_del(&root->snapshot_kobj);
}