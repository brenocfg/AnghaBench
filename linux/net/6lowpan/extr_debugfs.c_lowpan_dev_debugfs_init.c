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
struct lowpan_dev {int /*<<< orphan*/  ctx; void* iface_debugfs; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int LOWPAN_IPHC_CTX_TABLE_SIZE ; 
 void* debugfs_create_dir (char*,void*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lowpan_context_fops ; 
 void* lowpan_debugfs ; 
 struct lowpan_dev* lowpan_dev (struct net_device*) ; 
 int /*<<< orphan*/  lowpan_dev_debugfs_802154_init (struct net_device*,struct lowpan_dev*) ; 
 int /*<<< orphan*/  lowpan_dev_debugfs_ctx_init (struct net_device*,struct dentry*,int) ; 

void lowpan_dev_debugfs_init(struct net_device *dev)
{
	struct lowpan_dev *ldev = lowpan_dev(dev);
	struct dentry *contexts;
	int i;

	/* creating the root */
	ldev->iface_debugfs = debugfs_create_dir(dev->name, lowpan_debugfs);

	contexts = debugfs_create_dir("contexts", ldev->iface_debugfs);

	debugfs_create_file("show", 0644, contexts, &lowpan_dev(dev)->ctx,
			    &lowpan_context_fops);

	for (i = 0; i < LOWPAN_IPHC_CTX_TABLE_SIZE; i++)
		lowpan_dev_debugfs_ctx_init(dev, contexts, i);

	lowpan_dev_debugfs_802154_init(dev, ldev);
}