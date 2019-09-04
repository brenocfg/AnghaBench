#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fw_stats_update; int /*<<< orphan*/  fw_stats; int /*<<< orphan*/  fw_stats_len; } ;
struct wl1271 {TYPE_1__ stats; TYPE_3__* hw; } ;
struct dentry {int dummy; } ;
struct TYPE_6__ {TYPE_2__* wiphy; } ;
struct TYPE_5__ {int /*<<< orphan*/  debugfsdir; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int PTR_ERR (struct dentry*) ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl1271_debugfs_add_files (struct wl1271*,struct dentry*) ; 
 int /*<<< orphan*/  wl1271_debugfs_exit (struct wl1271*) ; 
 int wlcore_debugfs_init (struct wl1271*,struct dentry*) ; 

int wl1271_debugfs_init(struct wl1271 *wl)
{
	int ret;
	struct dentry *rootdir;

	rootdir = debugfs_create_dir(KBUILD_MODNAME,
				     wl->hw->wiphy->debugfsdir);

	if (IS_ERR(rootdir)) {
		ret = PTR_ERR(rootdir);
		goto out;
	}

	wl->stats.fw_stats = kzalloc(wl->stats.fw_stats_len, GFP_KERNEL);
	if (!wl->stats.fw_stats) {
		ret = -ENOMEM;
		goto out_remove;
	}

	wl->stats.fw_stats_update = jiffies;

	ret = wl1271_debugfs_add_files(wl, rootdir);
	if (ret < 0)
		goto out_exit;

	ret = wlcore_debugfs_init(wl, rootdir);
	if (ret < 0)
		goto out_exit;

	goto out;

out_exit:
	wl1271_debugfs_exit(wl);

out_remove:
	debugfs_remove_recursive(rootdir);

out:
	return ret;
}