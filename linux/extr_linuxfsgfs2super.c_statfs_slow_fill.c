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
struct gfs2_statfs_change_host {int /*<<< orphan*/  sc_dinodes; int /*<<< orphan*/  sc_free; int /*<<< orphan*/  sc_total; } ;
struct gfs2_rgrpd {scalar_t__ rd_dinodes; scalar_t__ rd_free; scalar_t__ rd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfs2_rgrp_verify (struct gfs2_rgrpd*) ; 

__attribute__((used)) static int statfs_slow_fill(struct gfs2_rgrpd *rgd,
			    struct gfs2_statfs_change_host *sc)
{
	gfs2_rgrp_verify(rgd);
	sc->sc_total += rgd->rd_data;
	sc->sc_free += rgd->rd_free;
	sc->sc_dinodes += rgd->rd_dinodes;
	return 0;
}