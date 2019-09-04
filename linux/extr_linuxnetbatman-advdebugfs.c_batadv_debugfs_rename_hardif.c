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
struct dentry {int /*<<< orphan*/  d_parent; } ;
struct batadv_hard_iface {struct dentry* debug_dir; TYPE_1__* net_dev; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 struct dentry* debugfs_rename (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

void batadv_debugfs_rename_hardif(struct batadv_hard_iface *hard_iface)
{
	const char *name = hard_iface->net_dev->name;
	struct dentry *dir;
	struct dentry *d;

	dir = hard_iface->debug_dir;
	if (!dir)
		return;

	d = debugfs_rename(dir->d_parent, dir, dir->d_parent, name);
	if (!d)
		pr_err("Can't rename debugfs dir to %s\n", name);
}