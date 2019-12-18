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
struct gfs2_sbd {int dummy; } ;
typedef  struct gfs2_rgrpd {struct gfs2_sbd* rd_sbd; } const gfs2_rgrpd ;

/* Variables and functions */
 struct gfs2_rgrpd const* gfs2_rgrpd_get_first (struct gfs2_sbd*) ; 
 struct gfs2_rgrpd const* gfs2_rgrpd_get_next (struct gfs2_rgrpd const*) ; 

__attribute__((used)) static bool gfs2_select_rgrp(struct gfs2_rgrpd **pos, const struct gfs2_rgrpd *begin)
{
	struct gfs2_rgrpd *rgd = *pos;
	struct gfs2_sbd *sdp = rgd->rd_sbd;

	rgd = gfs2_rgrpd_get_next(rgd);
	if (rgd == NULL)
		rgd = gfs2_rgrpd_get_first(sdp);
	*pos = rgd;
	if (rgd != begin) /* If we didn't wrap */
		return true;
	return false;
}