#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct buffer_head {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 TYPE_2__* AFFS_TAIL (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  EIO ; 
 struct dentry* ERR_CAST (struct inode*) ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct buffer_head* affs_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* affs_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 struct dentry* d_obtain_alias (struct inode*) ; 

__attribute__((used)) static struct dentry *affs_get_parent(struct dentry *child)
{
	struct inode *parent;
	struct buffer_head *bh;

	bh = affs_bread(child->d_sb, d_inode(child)->i_ino);
	if (!bh)
		return ERR_PTR(-EIO);

	parent = affs_iget(child->d_sb,
			   be32_to_cpu(AFFS_TAIL(child->d_sb, bh)->parent));
	brelse(bh);
	if (IS_ERR(parent))
		return ERR_CAST(parent);

	return d_obtain_alias(parent);
}