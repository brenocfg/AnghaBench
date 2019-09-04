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
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_rec {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct inode vfs_inode; } ;

/* Variables and functions */
 TYPE_1__* cache_info_to_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_extent_map_insert_rec (struct inode*,struct ocfs2_extent_rec*) ; 

__attribute__((used)) static void ocfs2_dinode_extent_map_insert(struct ocfs2_extent_tree *et,
					   struct ocfs2_extent_rec *rec)
{
	struct inode *inode = &cache_info_to_inode(et->et_ci)->vfs_inode;

	ocfs2_extent_map_insert_rec(inode, rec);
}