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
struct gfs2_rgrpd {int /*<<< orphan*/  rd_rsspin; } ;
struct TYPE_2__ {struct gfs2_rgrpd* rgd; } ;
struct gfs2_blkreserv {int /*<<< orphan*/  rs_free; TYPE_1__ rs_rbm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __rs_deltree (struct gfs2_blkreserv*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void gfs2_rs_deltree(struct gfs2_blkreserv *rs)
{
	struct gfs2_rgrpd *rgd;

	rgd = rs->rs_rbm.rgd;
	if (rgd) {
		spin_lock(&rgd->rd_rsspin);
		__rs_deltree(rs);
		BUG_ON(rs->rs_free);
		spin_unlock(&rgd->rd_rsspin);
	}
}