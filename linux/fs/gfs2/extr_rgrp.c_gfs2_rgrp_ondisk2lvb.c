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
struct gfs2_rgrp_lvb {unsigned long __pad; int /*<<< orphan*/  rl_igeneration; int /*<<< orphan*/  rl_dinodes; int /*<<< orphan*/  rl_free; int /*<<< orphan*/  rl_flags; int /*<<< orphan*/  rl_magic; } ;
struct gfs2_rgrp {int /*<<< orphan*/  rg_igeneration; int /*<<< orphan*/  rg_dinodes; int /*<<< orphan*/  rg_free; int /*<<< orphan*/  rg_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_MAGIC ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfs2_rgrp_ondisk2lvb(struct gfs2_rgrp_lvb *rgl, const void *buf)
{
	const struct gfs2_rgrp *str = buf;

	rgl->rl_magic = cpu_to_be32(GFS2_MAGIC);
	rgl->rl_flags = str->rg_flags;
	rgl->rl_free = str->rg_free;
	rgl->rl_dinodes = str->rg_dinodes;
	rgl->rl_igeneration = str->rg_igeneration;
	rgl->__pad = 0UL;
}