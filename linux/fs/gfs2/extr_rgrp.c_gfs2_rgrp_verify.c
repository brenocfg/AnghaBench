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
typedef  int u32 ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_rgrpd {int rd_length; int rd_free; int rd_data; int rd_dinodes; struct gfs2_bitmap* rd_bits; struct gfs2_sbd* rd_sbd; } ;
struct gfs2_bitmap {int /*<<< orphan*/  bi_bytes; scalar_t__ bi_offset; TYPE_1__* bi_bh; } ;
struct TYPE_2__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,int,int) ; 
 int gfs2_bitcount (struct gfs2_rgrpd*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ gfs2_consist_rgrpd (struct gfs2_rgrpd*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void gfs2_rgrp_verify(struct gfs2_rgrpd *rgd)
{
	struct gfs2_sbd *sdp = rgd->rd_sbd;
	struct gfs2_bitmap *bi = NULL;
	u32 length = rgd->rd_length;
	u32 count[4], tmp;
	int buf, x;

	memset(count, 0, 4 * sizeof(u32));

	/* Count # blocks in each of 4 possible allocation states */
	for (buf = 0; buf < length; buf++) {
		bi = rgd->rd_bits + buf;
		for (x = 0; x < 4; x++)
			count[x] += gfs2_bitcount(rgd,
						  bi->bi_bh->b_data +
						  bi->bi_offset,
						  bi->bi_bytes, x);
	}

	if (count[0] != rgd->rd_free) {
		if (gfs2_consist_rgrpd(rgd))
			fs_err(sdp, "free data mismatch:  %u != %u\n",
			       count[0], rgd->rd_free);
		return;
	}

	tmp = rgd->rd_data - rgd->rd_free - rgd->rd_dinodes;
	if (count[1] != tmp) {
		if (gfs2_consist_rgrpd(rgd))
			fs_err(sdp, "used data mismatch:  %u != %u\n",
			       count[1], tmp);
		return;
	}

	if (count[2] + count[3] != rgd->rd_dinodes) {
		if (gfs2_consist_rgrpd(rgd))
			fs_err(sdp, "used metadata mismatch:  %u != %u\n",
			       count[2] + count[3], rgd->rd_dinodes);
		return;
	}
}