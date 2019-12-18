#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ ar_rgrplvb; } ;
struct gfs2_sbd {TYPE_1__ sd_args; } ;
struct gfs2_rgrpd {unsigned int rd_length; int rd_flags; struct gfs2_bitmap* rd_bits; TYPE_2__* rd_rgl; int /*<<< orphan*/  rd_free; int /*<<< orphan*/  rd_extfail_pt; int /*<<< orphan*/  rd_free_clone; scalar_t__ rd_addr; struct gfs2_glock* rd_gl; struct gfs2_sbd* rd_sbd; } ;
struct gfs2_glock {int dummy; } ;
struct gfs2_bitmap {int /*<<< orphan*/  bi_clone; TYPE_3__* bi_bh; int /*<<< orphan*/  bi_flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  b_data; } ;
struct TYPE_8__ {scalar_t__ rl_magic; scalar_t__ rl_unlinked; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GBF_FULL ; 
 int /*<<< orphan*/  GFS2_MAGIC ; 
 int /*<<< orphan*/  GFS2_METATYPE_RB ; 
 int /*<<< orphan*/  GFS2_METATYPE_RG ; 
 int GFS2_RDF_CHECK ; 
 int GFS2_RDF_UPTODATE ; 
 int /*<<< orphan*/  brelse (TYPE_3__*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  count_unlinked (struct gfs2_rgrpd*) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_assert_warn (struct gfs2_sbd*,int) ; 
 int /*<<< orphan*/  gfs2_consist_rgrpd (struct gfs2_rgrpd*) ; 
 int gfs2_meta_read (struct gfs2_glock*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int gfs2_meta_wait (struct gfs2_sbd*,TYPE_3__*) ; 
 scalar_t__ gfs2_metatype_check (struct gfs2_sbd*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_rgrp_in (struct gfs2_rgrpd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_rgrp_lvb_valid (struct gfs2_rgrpd*) ; 
 int /*<<< orphan*/  gfs2_rgrp_ondisk2lvb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfs2_rgrp_bh_get(struct gfs2_rgrpd *rgd)
{
	struct gfs2_sbd *sdp = rgd->rd_sbd;
	struct gfs2_glock *gl = rgd->rd_gl;
	unsigned int length = rgd->rd_length;
	struct gfs2_bitmap *bi;
	unsigned int x, y;
	int error;

	if (rgd->rd_bits[0].bi_bh != NULL)
		return 0;

	for (x = 0; x < length; x++) {
		bi = rgd->rd_bits + x;
		error = gfs2_meta_read(gl, rgd->rd_addr + x, 0, 0, &bi->bi_bh);
		if (error)
			goto fail;
	}

	for (y = length; y--;) {
		bi = rgd->rd_bits + y;
		error = gfs2_meta_wait(sdp, bi->bi_bh);
		if (error)
			goto fail;
		if (gfs2_metatype_check(sdp, bi->bi_bh, y ? GFS2_METATYPE_RB :
					      GFS2_METATYPE_RG)) {
			error = -EIO;
			goto fail;
		}
	}

	if (!(rgd->rd_flags & GFS2_RDF_UPTODATE)) {
		for (x = 0; x < length; x++)
			clear_bit(GBF_FULL, &rgd->rd_bits[x].bi_flags);
		gfs2_rgrp_in(rgd, (rgd->rd_bits[0].bi_bh)->b_data);
		rgd->rd_flags |= (GFS2_RDF_UPTODATE | GFS2_RDF_CHECK);
		rgd->rd_free_clone = rgd->rd_free;
		/* max out the rgrp allocation failure point */
		rgd->rd_extfail_pt = rgd->rd_free;
	}
	if (cpu_to_be32(GFS2_MAGIC) != rgd->rd_rgl->rl_magic) {
		rgd->rd_rgl->rl_unlinked = cpu_to_be32(count_unlinked(rgd));
		gfs2_rgrp_ondisk2lvb(rgd->rd_rgl,
				     rgd->rd_bits[0].bi_bh->b_data);
	}
	else if (sdp->sd_args.ar_rgrplvb) {
		if (!gfs2_rgrp_lvb_valid(rgd)){
			gfs2_consist_rgrpd(rgd);
			error = -EIO;
			goto fail;
		}
		if (rgd->rd_rgl->rl_unlinked == 0)
			rgd->rd_flags &= ~GFS2_RDF_CHECK;
	}
	return 0;

fail:
	while (x--) {
		bi = rgd->rd_bits + x;
		brelse(bi->bi_bh);
		bi->bi_bh = NULL;
		gfs2_assert_warn(sdp, !bi->bi_clone);
	}

	return error;
}