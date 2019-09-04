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
struct gfs2_rbm {int offset; TYPE_2__* rgd; } ;
struct gfs2_bitmap {unsigned int bi_len; int bi_offset; unsigned int bi_start; unsigned char* bi_clone; TYPE_1__* bi_bh; } ;
struct TYPE_4__ {scalar_t__ rd_addr; } ;
struct TYPE_3__ {unsigned char* b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned char GFS2_BIT_MASK ; 
 int GFS2_BIT_SIZE ; 
 int GFS2_NBBY ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  gfs2_consist_rgrpd (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned long long,unsigned int,...) ; 
 struct gfs2_bitmap* rbm_bi (struct gfs2_rbm const*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * valid_change ; 

__attribute__((used)) static inline void gfs2_setbit(const struct gfs2_rbm *rbm, bool do_clone,
			       unsigned char new_state)
{
	unsigned char *byte1, *byte2, *end, cur_state;
	struct gfs2_bitmap *bi = rbm_bi(rbm);
	unsigned int buflen = bi->bi_len;
	const unsigned int bit = (rbm->offset % GFS2_NBBY) * GFS2_BIT_SIZE;

	byte1 = bi->bi_bh->b_data + bi->bi_offset + (rbm->offset / GFS2_NBBY);
	end = bi->bi_bh->b_data + bi->bi_offset + buflen;

	BUG_ON(byte1 >= end);

	cur_state = (*byte1 >> bit) & GFS2_BIT_MASK;

	if (unlikely(!valid_change[new_state * 4 + cur_state])) {
		pr_warn("buf_blk = 0x%x old_state=%d, new_state=%d\n",
			rbm->offset, cur_state, new_state);
		pr_warn("rgrp=0x%llx bi_start=0x%x\n",
			(unsigned long long)rbm->rgd->rd_addr, bi->bi_start);
		pr_warn("bi_offset=0x%x bi_len=0x%x\n",
			bi->bi_offset, bi->bi_len);
		dump_stack();
		gfs2_consist_rgrpd(rbm->rgd);
		return;
	}
	*byte1 ^= (cur_state ^ new_state) << bit;

	if (do_clone && bi->bi_clone) {
		byte2 = bi->bi_clone + bi->bi_offset + (rbm->offset / GFS2_NBBY);
		cur_state = (*byte2 >> bit) & GFS2_BIT_MASK;
		*byte2 ^= (cur_state ^ new_state) << bit;
	}
}