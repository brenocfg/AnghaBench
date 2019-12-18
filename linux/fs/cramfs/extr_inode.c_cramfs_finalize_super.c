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
struct super_block {int /*<<< orphan*/  s_root; int /*<<< orphan*/ * s_op; scalar_t__ s_time_max; scalar_t__ s_time_min; int /*<<< orphan*/  s_flags; } ;
struct inode {int dummy; } ;
struct cramfs_inode {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  SB_RDONLY ; 
 int /*<<< orphan*/  cramfs_ops ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 struct inode* get_cramfs_inode (struct super_block*,struct cramfs_inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cramfs_finalize_super(struct super_block *sb,
				 struct cramfs_inode *cramfs_root)
{
	struct inode *root;

	/* Set it all up.. */
	sb->s_flags |= SB_RDONLY;
	sb->s_time_min = 0;
	sb->s_time_max = 0;
	sb->s_op = &cramfs_ops;
	root = get_cramfs_inode(sb, cramfs_root, 0);
	if (IS_ERR(root))
		return PTR_ERR(root);
	sb->s_root = d_make_root(root);
	if (!sb->s_root)
		return -ENOMEM;
	return 0;
}