#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net {int dummy; } ;
struct dentry {int dummy; } ;
struct batadv_hard_iface {int /*<<< orphan*/ * debug_dir; TYPE_2__* net_dev; } ;
struct TYPE_4__ {int mode; int /*<<< orphan*/  name; } ;
struct batadv_debuginfo {int /*<<< orphan*/  fops; TYPE_1__ attr; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int S_IFREG ; 
 int /*<<< orphan*/  batadv_debugfs ; 
 struct batadv_debuginfo** batadv_hardif_debuginfos ; 
 int /*<<< orphan*/ * debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 struct net* dev_net (TYPE_2__*) ; 
 struct net init_net ; 

int batadv_debugfs_add_hardif(struct batadv_hard_iface *hard_iface)
{
	struct net *net = dev_net(hard_iface->net_dev);
	struct batadv_debuginfo **bat_debug;
	struct dentry *file;

	if (!batadv_debugfs)
		goto out;

	if (net != &init_net)
		return 0;

	hard_iface->debug_dir = debugfs_create_dir(hard_iface->net_dev->name,
						   batadv_debugfs);
	if (!hard_iface->debug_dir)
		goto out;

	for (bat_debug = batadv_hardif_debuginfos; *bat_debug; ++bat_debug) {
		file = debugfs_create_file(((*bat_debug)->attr).name,
					   S_IFREG | ((*bat_debug)->attr).mode,
					   hard_iface->debug_dir,
					   hard_iface->net_dev,
					   &(*bat_debug)->fops);
		if (!file)
			goto rem_attr;
	}

	return 0;
rem_attr:
	debugfs_remove_recursive(hard_iface->debug_dir);
	hard_iface->debug_dir = NULL;
out:
	return -ENOMEM;
}