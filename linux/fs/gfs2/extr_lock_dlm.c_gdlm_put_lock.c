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
struct lm_lockstruct {int /*<<< orphan*/  ls_dlm; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_flags; struct lm_lockstruct sd_lockstruct; } ;
struct TYPE_4__ {scalar_t__ ln_number; int /*<<< orphan*/  ln_type; struct gfs2_sbd* ln_sbd; } ;
struct TYPE_3__ {scalar_t__ sb_lkid; scalar_t__ sb_lvbptr; } ;
struct gfs2_glock {scalar_t__ gl_state; TYPE_2__ gl_name; TYPE_1__ gl_lksb; int /*<<< orphan*/  gl_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LKF_VALBLK ; 
 int /*<<< orphan*/  GFS2_LKS_DCOUNT ; 
 int /*<<< orphan*/  GLF_BLOCKING ; 
 scalar_t__ LM_ST_EXCLUSIVE ; 
 int /*<<< orphan*/  SDF_SKIP_DLM_UNLOCK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dlm_unlock (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gfs2_glock*) ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,int /*<<< orphan*/ ,unsigned long long,int) ; 
 int /*<<< orphan*/  gfs2_glock_free (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_glstats_inc (struct gfs2_glock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_sbstats_inc (struct gfs2_glock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_update_request_times (struct gfs2_glock*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gdlm_put_lock(struct gfs2_glock *gl)
{
	struct gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	struct lm_lockstruct *ls = &sdp->sd_lockstruct;
	int lvb_needs_unlock = 0;
	int error;

	if (gl->gl_lksb.sb_lkid == 0) {
		gfs2_glock_free(gl);
		return;
	}

	clear_bit(GLF_BLOCKING, &gl->gl_flags);
	gfs2_glstats_inc(gl, GFS2_LKS_DCOUNT);
	gfs2_sbstats_inc(gl, GFS2_LKS_DCOUNT);
	gfs2_update_request_times(gl);

	/* don't want to skip dlm_unlock writing the lvb when lock is ex */

	if (gl->gl_lksb.sb_lvbptr && (gl->gl_state == LM_ST_EXCLUSIVE))
		lvb_needs_unlock = 1;

	if (test_bit(SDF_SKIP_DLM_UNLOCK, &sdp->sd_flags) &&
	    !lvb_needs_unlock) {
		gfs2_glock_free(gl);
		return;
	}

	error = dlm_unlock(ls->ls_dlm, gl->gl_lksb.sb_lkid, DLM_LKF_VALBLK,
			   NULL, gl);
	if (error) {
		fs_err(sdp, "gdlm_unlock %x,%llx err=%d\n",
		       gl->gl_name.ln_type,
		       (unsigned long long)gl->gl_name.ln_number, error);
		return;
	}
}