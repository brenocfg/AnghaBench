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
typedef  int u32 ;
struct gfs2_rgrpd {int rd_flags; int rd_free; int rd_dinodes; scalar_t__ rd_addr; int rd_data; int rd_bitbytes; int /*<<< orphan*/  rd_rgl; int /*<<< orphan*/  rd_data0; int /*<<< orphan*/  rd_igeneration; } ;
struct gfs2_rgrp {int /*<<< orphan*/  rg_reserved; void* rg_crc; void* rg_bitbytes; void* rg_data; void* rg_data0; void* rg_igeneration; void* rg_skip; void* rg_dinodes; void* rg_free; void* rg_flags; } ;

/* Variables and functions */
 int GFS2_RDF_MASK ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int gfs2_disk_hash (void*,int) ; 
 int /*<<< orphan*/  gfs2_rgrp_ondisk2lvb (int /*<<< orphan*/ ,void*) ; 
 struct gfs2_rgrpd* gfs2_rgrpd_get_next (struct gfs2_rgrpd*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gfs2_rgrp_out(struct gfs2_rgrpd *rgd, void *buf)
{
	struct gfs2_rgrpd *next = gfs2_rgrpd_get_next(rgd);
	struct gfs2_rgrp *str = buf;
	u32 crc;

	str->rg_flags = cpu_to_be32(rgd->rd_flags & ~GFS2_RDF_MASK);
	str->rg_free = cpu_to_be32(rgd->rd_free);
	str->rg_dinodes = cpu_to_be32(rgd->rd_dinodes);
	if (next == NULL)
		str->rg_skip = 0;
	else if (next->rd_addr > rgd->rd_addr)
		str->rg_skip = cpu_to_be32(next->rd_addr - rgd->rd_addr);
	str->rg_igeneration = cpu_to_be64(rgd->rd_igeneration);
	str->rg_data0 = cpu_to_be64(rgd->rd_data0);
	str->rg_data = cpu_to_be32(rgd->rd_data);
	str->rg_bitbytes = cpu_to_be32(rgd->rd_bitbytes);
	str->rg_crc = 0;
	crc = gfs2_disk_hash(buf, sizeof(struct gfs2_rgrp));
	str->rg_crc = cpu_to_be32(crc);

	memset(&str->rg_reserved, 0, sizeof(str->rg_reserved));
	gfs2_rgrp_ondisk2lvb(rgd->rd_rgl, buf);
}