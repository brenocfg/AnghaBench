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
struct gfs2_sbd {int dummy; } ;
struct gfs2_rgrpd {scalar_t__ rd_addr; struct gfs2_sbd* rd_sbd; TYPE_2__* rd_bits; struct gfs2_rgrp_lvb* rd_rgl; } ;
struct gfs2_rgrp_lvb {scalar_t__ rl_flags; scalar_t__ rl_free; scalar_t__ rl_dinodes; scalar_t__ rl_igeneration; } ;
struct gfs2_rgrp {scalar_t__ rg_flags; scalar_t__ rg_free; scalar_t__ rg_dinodes; scalar_t__ rg_igeneration; } ;
struct TYPE_4__ {TYPE_1__* bi_bh; } ;
struct TYPE_3__ {scalar_t__ b_data; } ;

/* Variables and functions */
 unsigned long long be32_to_cpu (scalar_t__) ; 
 scalar_t__ be64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  fs_warn (struct gfs2_sbd*,char*,unsigned long long,unsigned long long,unsigned long long) ; 

__attribute__((used)) static int gfs2_rgrp_lvb_valid(struct gfs2_rgrpd *rgd)
{
	struct gfs2_rgrp_lvb *rgl = rgd->rd_rgl;
	struct gfs2_rgrp *str = (struct gfs2_rgrp *)rgd->rd_bits[0].bi_bh->b_data;
	struct gfs2_sbd *sdp = rgd->rd_sbd;
	int valid = 1;

	if (rgl->rl_flags != str->rg_flags) {
		fs_warn(sdp, "GFS2: rgd: %llu lvb flag mismatch %u/%u",
			(unsigned long long)rgd->rd_addr,
		       be32_to_cpu(rgl->rl_flags), be32_to_cpu(str->rg_flags));
		valid = 0;
	}
	if (rgl->rl_free != str->rg_free) {
		fs_warn(sdp, "GFS2: rgd: %llu lvb free mismatch %u/%u",
			(unsigned long long)rgd->rd_addr,
			be32_to_cpu(rgl->rl_free), be32_to_cpu(str->rg_free));
		valid = 0;
	}
	if (rgl->rl_dinodes != str->rg_dinodes) {
		fs_warn(sdp, "GFS2: rgd: %llu lvb dinode mismatch %u/%u",
			(unsigned long long)rgd->rd_addr,
			be32_to_cpu(rgl->rl_dinodes),
			be32_to_cpu(str->rg_dinodes));
		valid = 0;
	}
	if (rgl->rl_igeneration != str->rg_igeneration) {
		fs_warn(sdp, "GFS2: rgd: %llu lvb igen mismatch %llu/%llu",
			(unsigned long long)rgd->rd_addr,
			(unsigned long long)be64_to_cpu(rgl->rl_igeneration),
			(unsigned long long)be64_to_cpu(str->rg_igeneration));
		valid = 0;
	}
	return valid;
}