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
struct net_device {char* name; } ;
struct dentry {int /*<<< orphan*/  d_parent; } ;
struct batadv_priv {struct dentry* debug_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_rename (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ,char const*) ; 
 struct batadv_priv* netdev_priv (struct net_device*) ; 

void batadv_debugfs_rename_meshif(struct net_device *dev)
{
	struct batadv_priv *bat_priv = netdev_priv(dev);
	const char *name = dev->name;
	struct dentry *dir;

	dir = bat_priv->debug_dir;
	if (!dir)
		return;

	debugfs_rename(dir->d_parent, dir, dir->d_parent, name);
}