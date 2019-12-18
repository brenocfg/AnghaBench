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
struct seq_file {int /*<<< orphan*/  private; } ;
struct inode {int /*<<< orphan*/  i_private; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GOSSIP_DEBUGFS_DEBUG ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  help_debug_ops ; 
 scalar_t__ orangefs_debug_disabled ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int orangefs_debug_help_open(struct inode *inode, struct file *file)
{
	int rc = -ENODEV;
	int ret;

	gossip_debug(GOSSIP_DEBUGFS_DEBUG,
		     "orangefs_debug_help_open: start\n");

	if (orangefs_debug_disabled)
		goto out;

	ret = seq_open(file, &help_debug_ops);
	if (ret)
		goto out;

	((struct seq_file *)(file->private_data))->private = inode->i_private;

	rc = 0;

out:
	gossip_debug(GOSSIP_DEBUGFS_DEBUG,
		     "orangefs_debug_help_open: rc:%d:\n",
		     rc);
	return rc;
}