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
struct gfs2_rgrpd {TYPE_2__* rd_bits; struct gfs2_rgrp_lvb* rd_rgl; } ;
struct gfs2_rgrp_lvb {scalar_t__ rl_flags; scalar_t__ rl_free; scalar_t__ rl_dinodes; scalar_t__ rl_igeneration; } ;
struct gfs2_rgrp {scalar_t__ rg_flags; scalar_t__ rg_free; scalar_t__ rg_dinodes; scalar_t__ rg_igeneration; } ;
struct TYPE_4__ {TYPE_1__* bi_bh; } ;
struct TYPE_3__ {scalar_t__ b_data; } ;

/* Variables and functions */

__attribute__((used)) static int gfs2_rgrp_lvb_valid(struct gfs2_rgrpd *rgd)
{
	struct gfs2_rgrp_lvb *rgl = rgd->rd_rgl;
	struct gfs2_rgrp *str = (struct gfs2_rgrp *)rgd->rd_bits[0].bi_bh->b_data;

	if (rgl->rl_flags != str->rg_flags || rgl->rl_free != str->rg_free ||
	    rgl->rl_dinodes != str->rg_dinodes ||
	    rgl->rl_igeneration != str->rg_igeneration)
		return 0;
	return 1;
}