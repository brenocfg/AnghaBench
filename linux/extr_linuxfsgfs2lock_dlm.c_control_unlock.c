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
struct lm_lockstruct {int /*<<< orphan*/  ls_control_lksb; } ;
struct gfs2_sbd {struct lm_lockstruct sd_lockstruct; } ;

/* Variables and functions */
 int sync_unlock (struct gfs2_sbd*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int control_unlock(struct gfs2_sbd *sdp)
{
	struct lm_lockstruct *ls = &sdp->sd_lockstruct;
	return sync_unlock(sdp, &ls->ls_control_lksb, "control_lock");
}