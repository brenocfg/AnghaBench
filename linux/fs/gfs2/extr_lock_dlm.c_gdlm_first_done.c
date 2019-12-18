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
struct lm_lockstruct {int /*<<< orphan*/  ls_recover_flags; } ;
struct gfs2_sbd {struct lm_lockstruct sd_lockstruct; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFL_NO_DLM_OPS ; 
 int control_first_done (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gdlm_first_done(struct gfs2_sbd *sdp)
{
	struct lm_lockstruct *ls = &sdp->sd_lockstruct;
	int error;

	if (test_bit(DFL_NO_DLM_OPS, &ls->ls_recover_flags))
		return;

	error = control_first_done(sdp);
	if (error)
		fs_err(sdp, "mount first_done error %d\n", error);
}