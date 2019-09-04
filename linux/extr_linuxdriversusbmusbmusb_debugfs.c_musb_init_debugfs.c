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
struct musb {struct dentry* debugfs_root; int /*<<< orphan*/  controller; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IWUSR ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct musb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_regdump_fops ; 
 int /*<<< orphan*/  musb_softconnect_fops ; 
 int /*<<< orphan*/  musb_test_mode_fops ; 

void musb_init_debugfs(struct musb *musb)
{
	struct dentry *root;

	root = debugfs_create_dir(dev_name(musb->controller), NULL);
	musb->debugfs_root = root;

	debugfs_create_file("regdump", S_IRUGO, root, musb, &musb_regdump_fops);
	debugfs_create_file("testmode", S_IRUGO | S_IWUSR, root, musb,
			    &musb_test_mode_fops);
	debugfs_create_file("softconnect", S_IRUGO | S_IWUSR, root, musb,
			    &musb_softconnect_fops);
}