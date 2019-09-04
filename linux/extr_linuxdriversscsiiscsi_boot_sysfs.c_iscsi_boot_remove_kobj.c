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
struct iscsi_boot_kobj {int /*<<< orphan*/  kobj; int /*<<< orphan*/  attr_group; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iscsi_boot_remove_kobj(struct iscsi_boot_kobj *boot_kobj)
{
	list_del(&boot_kobj->list);
	sysfs_remove_group(&boot_kobj->kobj, boot_kobj->attr_group);
	kobject_put(&boot_kobj->kobj);
}