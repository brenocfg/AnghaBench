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
struct gfs2_rgrpd {int rd_flags; TYPE_1__* rd_rgl; int /*<<< orphan*/  rd_igeneration; void* rd_dinodes; void* rd_free; void* rd_free_clone; } ;
struct TYPE_2__ {scalar_t__ rl_magic; scalar_t__ rl_unlinked; int /*<<< orphan*/  rl_igeneration; int /*<<< orphan*/  rl_dinodes; int /*<<< orphan*/  rl_free; int /*<<< orphan*/  rl_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_MAGIC ; 
 int GFS2_RDF_CHECK ; 
 int GFS2_RDF_MASK ; 
 int GFS2_RDF_UPTODATE ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int gfs2_rgrp_bh_get (struct gfs2_rgrpd*) ; 

__attribute__((used)) static int update_rgrp_lvb(struct gfs2_rgrpd *rgd)
{
	u32 rl_flags;

	if (rgd->rd_flags & GFS2_RDF_UPTODATE)
		return 0;

	if (cpu_to_be32(GFS2_MAGIC) != rgd->rd_rgl->rl_magic)
		return gfs2_rgrp_bh_get(rgd);

	rl_flags = be32_to_cpu(rgd->rd_rgl->rl_flags);
	rl_flags &= ~GFS2_RDF_MASK;
	rgd->rd_flags &= GFS2_RDF_MASK;
	rgd->rd_flags |= (rl_flags | GFS2_RDF_CHECK);
	if (rgd->rd_rgl->rl_unlinked == 0)
		rgd->rd_flags &= ~GFS2_RDF_CHECK;
	rgd->rd_free = be32_to_cpu(rgd->rd_rgl->rl_free);
	rgd->rd_free_clone = rgd->rd_free;
	rgd->rd_dinodes = be32_to_cpu(rgd->rd_rgl->rl_dinodes);
	rgd->rd_igeneration = be64_to_cpu(rgd->rd_rgl->rl_igeneration);
	return 0;
}