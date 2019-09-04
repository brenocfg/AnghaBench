#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * rootdir; int /*<<< orphan*/ * fw_statistics; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fw_stats; int /*<<< orphan*/  fw_stats_update; } ;
struct wl1251 {TYPE_2__ debugfs; TYPE_1__ stats; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 char* KBUILD_MODNAME ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 void* debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_debugfs_add_files (struct wl1251*) ; 

int wl1251_debugfs_init(struct wl1251 *wl)
{
	int ret;

	wl->debugfs.rootdir = debugfs_create_dir(KBUILD_MODNAME, NULL);

	if (IS_ERR(wl->debugfs.rootdir)) {
		ret = PTR_ERR(wl->debugfs.rootdir);
		wl->debugfs.rootdir = NULL;
		goto err;
	}

	wl->debugfs.fw_statistics = debugfs_create_dir("fw-statistics",
						       wl->debugfs.rootdir);

	if (IS_ERR(wl->debugfs.fw_statistics)) {
		ret = PTR_ERR(wl->debugfs.fw_statistics);
		wl->debugfs.fw_statistics = NULL;
		goto err_root;
	}

	wl->stats.fw_stats = kzalloc(sizeof(*wl->stats.fw_stats),
				      GFP_KERNEL);

	if (!wl->stats.fw_stats) {
		ret = -ENOMEM;
		goto err_fw;
	}

	wl->stats.fw_stats_update = jiffies;

	ret = wl1251_debugfs_add_files(wl);

	if (ret < 0)
		goto err_file;

	return 0;

err_file:
	kfree(wl->stats.fw_stats);
	wl->stats.fw_stats = NULL;

err_fw:
	debugfs_remove(wl->debugfs.fw_statistics);
	wl->debugfs.fw_statistics = NULL;

err_root:
	debugfs_remove(wl->debugfs.rootdir);
	wl->debugfs.rootdir = NULL;

err:
	return ret;
}