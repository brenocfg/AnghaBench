#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gfs2_rgrpd {int rd_length; struct gfs2_bitmap* rd_bits; } ;
struct gfs2_bitmap {int /*<<< orphan*/ * bi_bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 

void gfs2_rgrp_brelse(struct gfs2_rgrpd *rgd)
{
	int x, length = rgd->rd_length;

	for (x = 0; x < length; x++) {
		struct gfs2_bitmap *bi = rgd->rd_bits + x;
		if (bi->bi_bh) {
			brelse(bi->bi_bh);
			bi->bi_bh = NULL;
		}
	}

}