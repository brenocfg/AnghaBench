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
struct gfs2_rbm {scalar_t__ offset; scalar_t__ bii; TYPE_1__* rgd; } ;
struct TYPE_4__ {struct gfs2_rbm rs_rbm; } ;
struct gfs2_inode {scalar_t__ i_goal; TYPE_2__ i_res; } ;
struct TYPE_3__ {scalar_t__ rd_data0; scalar_t__ rd_last_alloc; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_rbm_from_block (struct gfs2_rbm*,scalar_t__) ; 
 scalar_t__ gfs2_rs_active (TYPE_2__*) ; 
 scalar_t__ rgrp_contains_block (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void gfs2_set_alloc_start(struct gfs2_rbm *rbm,
				 const struct gfs2_inode *ip, bool dinode)
{
	u64 goal;

	if (gfs2_rs_active(&ip->i_res)) {
		*rbm = ip->i_res.rs_rbm;
		return;
	}

	if (!dinode && rgrp_contains_block(rbm->rgd, ip->i_goal))
		goal = ip->i_goal;
	else
		goal = rbm->rgd->rd_last_alloc + rbm->rgd->rd_data0;

	if (WARN_ON_ONCE(gfs2_rbm_from_block(rbm, goal))) {
		rbm->bii = 0;
		rbm->offset = 0;
	}
}