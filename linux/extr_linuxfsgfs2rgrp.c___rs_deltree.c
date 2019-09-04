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
struct gfs2_rgrpd {scalar_t__ rd_reserved; int /*<<< orphan*/  rd_extfail_pt; int /*<<< orphan*/  rd_rstree; } ;
struct TYPE_2__ {struct gfs2_rgrpd* rgd; } ;
struct gfs2_blkreserv {scalar_t__ rs_free; TYPE_1__ rs_rbm; int /*<<< orphan*/  rs_node; } ;
struct gfs2_bitmap {int /*<<< orphan*/  bi_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GBF_FULL ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE_RS_TREEDEL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_rs_active (struct gfs2_blkreserv*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct gfs2_bitmap* rbm_bi (TYPE_1__*) ; 
 int /*<<< orphan*/  trace_gfs2_rs (struct gfs2_blkreserv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __rs_deltree(struct gfs2_blkreserv *rs)
{
	struct gfs2_rgrpd *rgd;

	if (!gfs2_rs_active(rs))
		return;

	rgd = rs->rs_rbm.rgd;
	trace_gfs2_rs(rs, TRACE_RS_TREEDEL);
	rb_erase(&rs->rs_node, &rgd->rd_rstree);
	RB_CLEAR_NODE(&rs->rs_node);

	if (rs->rs_free) {
		struct gfs2_bitmap *bi = rbm_bi(&rs->rs_rbm);

		/* return reserved blocks to the rgrp */
		BUG_ON(rs->rs_rbm.rgd->rd_reserved < rs->rs_free);
		rs->rs_rbm.rgd->rd_reserved -= rs->rs_free;
		/* The rgrp extent failure point is likely not to increase;
		   it will only do so if the freed blocks are somehow
		   contiguous with a span of free blocks that follows. Still,
		   it will force the number to be recalculated later. */
		rgd->rd_extfail_pt += rs->rs_free;
		rs->rs_free = 0;
		clear_bit(GBF_FULL, &bi->bi_flags);
	}
}