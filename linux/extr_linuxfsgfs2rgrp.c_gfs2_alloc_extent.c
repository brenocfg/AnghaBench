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
typedef  int /*<<< orphan*/  u64 ;
typedef  struct gfs2_rbm {TYPE_1__* rgd; } const gfs2_rbm ;
struct TYPE_4__ {int /*<<< orphan*/  bi_bh; } ;
struct TYPE_3__ {int /*<<< orphan*/  rd_gl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_BLKST_DINODE ; 
 scalar_t__ GFS2_BLKST_FREE ; 
 int /*<<< orphan*/  GFS2_BLKST_USED ; 
 int gfs2_rbm_from_block (struct gfs2_rbm const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_rbm_to_block (struct gfs2_rbm const*) ; 
 int /*<<< orphan*/  gfs2_setbit (struct gfs2_rbm const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gfs2_testbit (struct gfs2_rbm const*,int) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* rbm_bi (struct gfs2_rbm const*) ; 

__attribute__((used)) static void gfs2_alloc_extent(const struct gfs2_rbm *rbm, bool dinode,
			     unsigned int *n)
{
	struct gfs2_rbm pos = { .rgd = rbm->rgd, };
	const unsigned int elen = *n;
	u64 block;
	int ret;

	*n = 1;
	block = gfs2_rbm_to_block(rbm);
	gfs2_trans_add_meta(rbm->rgd->rd_gl, rbm_bi(rbm)->bi_bh);
	gfs2_setbit(rbm, true, dinode ? GFS2_BLKST_DINODE : GFS2_BLKST_USED);
	block++;
	while (*n < elen) {
		ret = gfs2_rbm_from_block(&pos, block);
		if (ret || gfs2_testbit(&pos, true) != GFS2_BLKST_FREE)
			break;
		gfs2_trans_add_meta(pos.rgd->rd_gl, rbm_bi(&pos)->bi_bh);
		gfs2_setbit(&pos, true, GFS2_BLKST_USED);
		(*n)++;
		block++;
	}
}