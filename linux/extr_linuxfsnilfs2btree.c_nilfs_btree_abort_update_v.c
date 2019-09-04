#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bpr_req; } ;
struct TYPE_4__ {int /*<<< orphan*/  bpr_req; } ;
struct nilfs_btree_path {int /*<<< orphan*/  bp_ctxt; int /*<<< orphan*/  bp_bh; TYPE_2__ bp_newreq; TYPE_1__ bp_oldreq; } ;
struct nilfs_bmap {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_btnode_cache; } ;

/* Variables and functions */
 TYPE_3__* NILFS_BMAP_I (struct nilfs_bmap*) ; 
 scalar_t__ buffer_nilfs_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_btnode_abort_change_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_dat_abort_update (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_btree_abort_update_v(struct nilfs_bmap *btree,
				       struct nilfs_btree_path *path,
				       int level, struct inode *dat)
{
	nilfs_dat_abort_update(dat, &path[level].bp_oldreq.bpr_req,
			       &path[level].bp_newreq.bpr_req);
	if (buffer_nilfs_node(path[level].bp_bh))
		nilfs_btnode_abort_change_key(
			&NILFS_BMAP_I(btree)->i_btnode_cache,
			&path[level].bp_ctxt);
}