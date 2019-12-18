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
typedef  int /*<<< orphan*/  uint32_t ;
struct lm_lockstruct {int /*<<< orphan*/  ls_sync_wait; int /*<<< orphan*/  ls_dlm; } ;
struct gfs2_sbd {struct lm_lockstruct sd_lockstruct; } ;
struct dlm_lksb {int sb_status; int /*<<< orphan*/  sb_lkid; } ;

/* Variables and functions */
 int EAGAIN ; 
 int GDLM_STRNAME_BYTES ; 
 int LM_TYPE_NONDISK ; 
 int dlm_lock (int /*<<< orphan*/ ,int,struct dlm_lksb*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lm_lockstruct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,unsigned int) ; 
 int /*<<< orphan*/  sync_wait_cb ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sync_lock(struct gfs2_sbd *sdp, int mode, uint32_t flags,
		     unsigned int num, struct dlm_lksb *lksb, char *name)
{
	struct lm_lockstruct *ls = &sdp->sd_lockstruct;
	char strname[GDLM_STRNAME_BYTES];
	int error, status;

	memset(strname, 0, GDLM_STRNAME_BYTES);
	snprintf(strname, GDLM_STRNAME_BYTES, "%8x%16x", LM_TYPE_NONDISK, num);

	error = dlm_lock(ls->ls_dlm, mode, lksb, flags,
			 strname, GDLM_STRNAME_BYTES - 1,
			 0, sync_wait_cb, ls, NULL);
	if (error) {
		fs_err(sdp, "%s lkid %x flags %x mode %d error %d\n",
		       name, lksb->sb_lkid, flags, mode, error);
		return error;
	}

	wait_for_completion(&ls->ls_sync_wait);

	status = lksb->sb_status;

	if (status && status != -EAGAIN) {
		fs_err(sdp, "%s lkid %x flags %x mode %d status %d\n",
		       name, lksb->sb_lkid, flags, mode, status);
	}

	return status;
}