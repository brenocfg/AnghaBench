#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct address_space {int dummy; } ;
struct gfs2_sbd {struct address_space sd_aspace; } ;
struct gfs2_rgrpd {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct TYPE_4__ {struct gfs2_sbd* ln_sbd; } ;
struct gfs2_glock {scalar_t__ gl_state; TYPE_3__ gl_lockref; struct gfs2_rgrpd* gl_object; TYPE_2__ gl_vm; int /*<<< orphan*/  gl_flags; TYPE_1__ gl_name; } ;

/* Variables and functions */
 int GFS2_LFC_RGRP_GO_SYNC ; 
 int GFS2_LOG_HEAD_FLUSH_NORMAL ; 
 int /*<<< orphan*/  GLF_DIRTY ; 
 int /*<<< orphan*/  GLOCK_BUG_ON (struct gfs2_glock*,int) ; 
 scalar_t__ LM_ST_EXCLUSIVE ; 
 int filemap_fdatawait_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filemap_fdatawrite_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_ail_empty_gl (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_free_clones (struct gfs2_rgrpd*) ; 
 int /*<<< orphan*/  gfs2_log_flush (struct gfs2_sbd*,struct gfs2_glock*,int) ; 
 int /*<<< orphan*/  gfs2_rgrp_brelse (struct gfs2_rgrpd*) ; 
 int /*<<< orphan*/  mapping_set_error (struct address_space*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rgrp_go_sync(struct gfs2_glock *gl)
{
	struct gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	struct address_space *mapping = &sdp->sd_aspace;
	struct gfs2_rgrpd *rgd;
	int error;

	spin_lock(&gl->gl_lockref.lock);
	rgd = gl->gl_object;
	if (rgd)
		gfs2_rgrp_brelse(rgd);
	spin_unlock(&gl->gl_lockref.lock);

	if (!test_and_clear_bit(GLF_DIRTY, &gl->gl_flags))
		return;
	GLOCK_BUG_ON(gl, gl->gl_state != LM_ST_EXCLUSIVE);

	gfs2_log_flush(sdp, gl, GFS2_LOG_HEAD_FLUSH_NORMAL |
		       GFS2_LFC_RGRP_GO_SYNC);
	filemap_fdatawrite_range(mapping, gl->gl_vm.start, gl->gl_vm.end);
	error = filemap_fdatawait_range(mapping, gl->gl_vm.start, gl->gl_vm.end);
	mapping_set_error(mapping, error);
	gfs2_ail_empty_gl(gl);

	spin_lock(&gl->gl_lockref.lock);
	rgd = gl->gl_object;
	if (rgd)
		gfs2_free_clones(rgd);
	spin_unlock(&gl->gl_lockref.lock);
}