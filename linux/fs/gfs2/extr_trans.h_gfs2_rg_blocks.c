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
struct gfs2_rgrpd {unsigned int rd_length; } ;
struct TYPE_3__ {struct gfs2_rgrpd* rgd; } ;
struct TYPE_4__ {TYPE_1__ rs_rbm; } ;
struct gfs2_inode {TYPE_2__ i_res; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int gfs2_rg_blocks(const struct gfs2_inode *ip, unsigned requested)
{
	struct gfs2_rgrpd *rgd = ip->i_res.rs_rbm.rgd;

	if (requested < rgd->rd_length)
		return requested + 1;
	return rgd->rd_length;
}