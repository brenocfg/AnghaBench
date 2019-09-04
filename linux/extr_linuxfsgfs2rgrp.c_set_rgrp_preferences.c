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
struct TYPE_2__ {int ls_jid; } ;
struct gfs2_sbd {int sd_journals; TYPE_1__ sd_lockstruct; } ;
struct gfs2_rgrpd {int /*<<< orphan*/  rd_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_RDF_PREFERRED ; 
 struct gfs2_rgrpd* gfs2_rgrpd_get_first (struct gfs2_sbd*) ; 
 struct gfs2_rgrpd* gfs2_rgrpd_get_next (struct gfs2_rgrpd*) ; 

__attribute__((used)) static void set_rgrp_preferences(struct gfs2_sbd *sdp)
{
	struct gfs2_rgrpd *rgd, *first;
	int i;

	/* Skip an initial number of rgrps, based on this node's journal ID.
	   That should start each node out on its own set. */
	rgd = gfs2_rgrpd_get_first(sdp);
	for (i = 0; i < sdp->sd_lockstruct.ls_jid; i++)
		rgd = gfs2_rgrpd_get_next(rgd);
	first = rgd;

	do {
		rgd->rd_flags |= GFS2_RDF_PREFERRED;
		for (i = 0; i < sdp->sd_journals; i++) {
			rgd = gfs2_rgrpd_get_next(rgd);
			if (!rgd || rgd == first)
				break;
		}
	} while (rgd && rgd != first);
}