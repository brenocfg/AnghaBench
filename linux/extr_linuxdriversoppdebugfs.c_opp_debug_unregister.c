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
struct opp_table {int /*<<< orphan*/ * dentry; int /*<<< orphan*/  dev_list; } ;
struct opp_device {int /*<<< orphan*/ * dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_is_singular (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opp_migrate_dentry (struct opp_device*,struct opp_table*) ; 

void opp_debug_unregister(struct opp_device *opp_dev,
			  struct opp_table *opp_table)
{
	if (opp_dev->dentry == opp_table->dentry) {
		/* Move the real dentry object under another device */
		if (!list_is_singular(&opp_table->dev_list)) {
			opp_migrate_dentry(opp_dev, opp_table);
			goto out;
		}
		opp_table->dentry = NULL;
	}

	debugfs_remove_recursive(opp_dev->dentry);

out:
	opp_dev->dentry = NULL;
}