#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  bpr_ptr; int /*<<< orphan*/  bpr_req; } ;
struct TYPE_7__ {int /*<<< orphan*/  bh; } ;
struct TYPE_5__ {int /*<<< orphan*/  bpr_req; } ;
struct nilfs_btree_path {TYPE_2__ bp_newreq; int /*<<< orphan*/  bp_index; int /*<<< orphan*/  bp_bh; TYPE_3__ bp_ctxt; TYPE_1__ bp_oldreq; } ;
struct nilfs_btree_node {int dummy; } ;
struct nilfs_bmap {scalar_t__ b_ptr_type; } ;
struct inode {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_btnode_cache; } ;

/* Variables and functions */
 TYPE_4__* NILFS_BMAP_I (struct nilfs_bmap*) ; 
 scalar_t__ NILFS_BMAP_PTR_VS ; 
 scalar_t__ buffer_nilfs_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_btnode_commit_change_key (int /*<<< orphan*/ *,TYPE_3__*) ; 
 struct nilfs_btree_node* nilfs_btree_get_node (struct nilfs_bmap*,struct nilfs_btree_path*,int,int*) ; 
 int /*<<< orphan*/  nilfs_btree_node_set_ptr (struct nilfs_btree_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nilfs_dat_commit_update (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_buffer_nilfs_volatile (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nilfs_btree_commit_update_v(struct nilfs_bmap *btree,
					struct nilfs_btree_path *path,
					int level, struct inode *dat)
{
	struct nilfs_btree_node *parent;
	int ncmax;

	nilfs_dat_commit_update(dat, &path[level].bp_oldreq.bpr_req,
				&path[level].bp_newreq.bpr_req,
				btree->b_ptr_type == NILFS_BMAP_PTR_VS);

	if (buffer_nilfs_node(path[level].bp_bh)) {
		nilfs_btnode_commit_change_key(
			&NILFS_BMAP_I(btree)->i_btnode_cache,
			&path[level].bp_ctxt);
		path[level].bp_bh = path[level].bp_ctxt.bh;
	}
	set_buffer_nilfs_volatile(path[level].bp_bh);

	parent = nilfs_btree_get_node(btree, path, level + 1, &ncmax);
	nilfs_btree_node_set_ptr(parent, path[level + 1].bp_index,
				 path[level].bp_newreq.bpr_ptr, ncmax);
}