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
struct ideapad_private {int /*<<< orphan*/ * debug; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debugfs_cfg_fops ; 
 int /*<<< orphan*/ * debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ideapad_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_status_fops ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int ideapad_debugfs_init(struct ideapad_private *priv)
{
	struct dentry *node;

	priv->debug = debugfs_create_dir("ideapad", NULL);
	if (priv->debug == NULL) {
		pr_err("failed to create debugfs directory");
		goto errout;
	}

	node = debugfs_create_file("cfg", S_IRUGO, priv->debug, priv,
				   &debugfs_cfg_fops);
	if (!node) {
		pr_err("failed to create cfg in debugfs");
		goto errout;
	}

	node = debugfs_create_file("status", S_IRUGO, priv->debug, priv,
				   &debugfs_status_fops);
	if (!node) {
		pr_err("failed to create status in debugfs");
		goto errout;
	}

	return 0;

errout:
	return -ENOMEM;
}