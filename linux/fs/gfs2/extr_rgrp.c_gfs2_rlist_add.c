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
typedef  scalar_t__ u64 ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_rgrpd {int dummy; } ;
struct gfs2_rgrp_list {int rl_rgrps; int rl_space; struct gfs2_rgrpd** rl_rgd; int /*<<< orphan*/  rl_ghs; } ;
struct TYPE_3__ {struct gfs2_rgrpd* rgd; } ;
struct TYPE_4__ {TYPE_1__ rs_rbm; } ;
struct gfs2_inode {TYPE_2__ i_res; int /*<<< orphan*/  i_inode; } ;

/* Variables and functions */
 int GFP_NOFS ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,unsigned long long) ; 
 scalar_t__ gfs2_assert_warn (struct gfs2_sbd*,int) ; 
 struct gfs2_rgrpd* gfs2_blk2rgrpd (struct gfs2_sbd*,scalar_t__,int) ; 
 struct gfs2_rgrpd** kcalloc (unsigned int,int,int) ; 
 int /*<<< orphan*/  kfree (struct gfs2_rgrpd**) ; 
 int /*<<< orphan*/  memcpy (struct gfs2_rgrpd**,struct gfs2_rgrpd**,int) ; 
 scalar_t__ rgrp_contains_block (struct gfs2_rgrpd*,scalar_t__) ; 
 int /*<<< orphan*/  swap (struct gfs2_rgrpd*,struct gfs2_rgrpd*) ; 

void gfs2_rlist_add(struct gfs2_inode *ip, struct gfs2_rgrp_list *rlist,
		    u64 block)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct gfs2_rgrpd *rgd;
	struct gfs2_rgrpd **tmp;
	unsigned int new_space;
	unsigned int x;

	if (gfs2_assert_warn(sdp, !rlist->rl_ghs))
		return;

	/*
	 * The resource group last accessed is kept in the last position.
	 */

	if (rlist->rl_rgrps) {
		rgd = rlist->rl_rgd[rlist->rl_rgrps - 1];
		if (rgrp_contains_block(rgd, block))
			return;
		rgd = gfs2_blk2rgrpd(sdp, block, 1);
	} else {
		rgd = ip->i_res.rs_rbm.rgd;
		if (!rgd || !rgrp_contains_block(rgd, block))
			rgd = gfs2_blk2rgrpd(sdp, block, 1);
	}

	if (!rgd) {
		fs_err(sdp, "rlist_add: no rgrp for block %llu\n",
		       (unsigned long long)block);
		return;
	}

	for (x = 0; x < rlist->rl_rgrps; x++) {
		if (rlist->rl_rgd[x] == rgd) {
			swap(rlist->rl_rgd[x],
			     rlist->rl_rgd[rlist->rl_rgrps - 1]);
			return;
		}
	}

	if (rlist->rl_rgrps == rlist->rl_space) {
		new_space = rlist->rl_space + 10;

		tmp = kcalloc(new_space, sizeof(struct gfs2_rgrpd *),
			      GFP_NOFS | __GFP_NOFAIL);

		if (rlist->rl_rgd) {
			memcpy(tmp, rlist->rl_rgd,
			       rlist->rl_space * sizeof(struct gfs2_rgrpd *));
			kfree(rlist->rl_rgd);
		}

		rlist->rl_space = new_space;
		rlist->rl_rgd = tmp;
	}

	rlist->rl_rgd[rlist->rl_rgrps++] = rgd;
}