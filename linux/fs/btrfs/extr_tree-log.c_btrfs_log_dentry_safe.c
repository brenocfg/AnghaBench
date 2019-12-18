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
struct dentry {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_log_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_INODE_ALL ; 
 int btrfs_log_inode_parent (struct btrfs_trans_handle*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,struct btrfs_log_ctx*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 

int btrfs_log_dentry_safe(struct btrfs_trans_handle *trans,
			  struct dentry *dentry,
			  const loff_t start,
			  const loff_t end,
			  struct btrfs_log_ctx *ctx)
{
	struct dentry *parent = dget_parent(dentry);
	int ret;

	ret = btrfs_log_inode_parent(trans, BTRFS_I(d_inode(dentry)), parent,
				     start, end, LOG_INODE_ALL, ctx);
	dput(parent);

	return ret;
}