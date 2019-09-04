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
struct wimax_dev {struct dentry* debugfs_dentry; struct net_device* net_dev; } ;
struct TYPE_2__ {struct device* parent; } ;
struct net_device {char* name; TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  __debugfs_register (char*,int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  debugfs ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  id_table ; 
 int /*<<< orphan*/  op_msg ; 
 int /*<<< orphan*/  op_reset ; 
 int /*<<< orphan*/  op_rfkill ; 
 int /*<<< orphan*/  op_state_get ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stack ; 

int wimax_debugfs_add(struct wimax_dev *wimax_dev)
{
	int result;
	struct net_device *net_dev = wimax_dev->net_dev;
	struct device *dev = net_dev->dev.parent;
	struct dentry *dentry;
	char buf[128];

	snprintf(buf, sizeof(buf), "wimax:%s", net_dev->name);
	dentry = debugfs_create_dir(buf, NULL);
	result = PTR_ERR(dentry);
	if (IS_ERR(dentry)) {
		if (result == -ENODEV)
			result = 0;	/* No debugfs support */
		else
			dev_err(dev, "Can't create debugfs dentry: %d\n",
				result);
		goto out;
	}
	wimax_dev->debugfs_dentry = dentry;
	__debugfs_register("wimax_dl_", debugfs, dentry);
	__debugfs_register("wimax_dl_", id_table, dentry);
	__debugfs_register("wimax_dl_", op_msg, dentry);
	__debugfs_register("wimax_dl_", op_reset, dentry);
	__debugfs_register("wimax_dl_", op_rfkill, dentry);
	__debugfs_register("wimax_dl_", op_state_get, dentry);
	__debugfs_register("wimax_dl_", stack, dentry);
	result = 0;
out:
	return result;

error:
	debugfs_remove_recursive(wimax_dev->debugfs_dentry);
	return result;
}