#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dentry {int dummy; } ;
struct TYPE_2__ {int mode; int /*<<< orphan*/  name; } ;
struct batadv_debuginfo {TYPE_1__ attr; int /*<<< orphan*/  fops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DEBUGFS_SUBDIR ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/ * ERR_PTR (int /*<<< orphan*/ ) ; 
 int S_IFREG ; 
 int /*<<< orphan*/ * batadv_debugfs ; 
 struct batadv_debuginfo** batadv_general_debuginfos ; 
 int /*<<< orphan*/ * debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

void batadv_debugfs_init(void)
{
	struct batadv_debuginfo **bat_debug;
	struct dentry *file;

	batadv_debugfs = debugfs_create_dir(BATADV_DEBUGFS_SUBDIR, NULL);
	if (batadv_debugfs == ERR_PTR(-ENODEV))
		batadv_debugfs = NULL;

	if (!batadv_debugfs)
		goto err;

	for (bat_debug = batadv_general_debuginfos; *bat_debug; ++bat_debug) {
		file = debugfs_create_file(((*bat_debug)->attr).name,
					   S_IFREG | ((*bat_debug)->attr).mode,
					   batadv_debugfs, NULL,
					   &(*bat_debug)->fops);
		if (!file) {
			pr_err("Can't add general debugfs file: %s\n",
			       ((*bat_debug)->attr).name);
			goto err;
		}
	}

	return;
err:
	debugfs_remove_recursive(batadv_debugfs);
	batadv_debugfs = NULL;
}