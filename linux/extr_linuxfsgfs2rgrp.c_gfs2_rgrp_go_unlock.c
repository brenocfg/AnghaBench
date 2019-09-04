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
struct gfs2_rgrpd {int dummy; } ;
struct gfs2_holder {TYPE_1__* gh_gl; } ;
struct TYPE_2__ {int /*<<< orphan*/  gl_flags; struct gfs2_rgrpd* gl_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLF_DEMOTE ; 
 int /*<<< orphan*/  GLF_PENDING_DEMOTE ; 
 int /*<<< orphan*/  gfs2_rgrp_brelse (struct gfs2_rgrpd*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gfs2_rgrp_go_unlock(struct gfs2_holder *gh)
{
	struct gfs2_rgrpd *rgd = gh->gh_gl->gl_object;
	int demote_requested = test_bit(GLF_DEMOTE, &gh->gh_gl->gl_flags) |
		test_bit(GLF_PENDING_DEMOTE, &gh->gh_gl->gl_flags);

	if (rgd && demote_requested)
		gfs2_rgrp_brelse(rgd);
}