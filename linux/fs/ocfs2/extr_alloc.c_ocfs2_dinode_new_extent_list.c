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
struct TYPE_3__ {int /*<<< orphan*/  l_count; scalar_t__ l_next_free_rec; scalar_t__ l_tree_depth; } ;
struct TYPE_4__ {TYPE_1__ i_list; } ;
struct ocfs2_dinode {TYPE_2__ id2; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_extent_recs_per_inode_with_xattr (int /*<<< orphan*/ ,struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  ocfs2_zero_dinode_id2_with_xattr (struct inode*,struct ocfs2_dinode*) ; 

void ocfs2_dinode_new_extent_list(struct inode *inode,
				  struct ocfs2_dinode *di)
{
	ocfs2_zero_dinode_id2_with_xattr(inode, di);
	di->id2.i_list.l_tree_depth = 0;
	di->id2.i_list.l_next_free_rec = 0;
	di->id2.i_list.l_count = cpu_to_le16(
		ocfs2_extent_recs_per_inode_with_xattr(inode->i_sb, di));
}