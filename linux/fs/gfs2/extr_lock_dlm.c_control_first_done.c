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
typedef  scalar_t__ uint32_t ;
struct lm_lockstruct {scalar_t__ ls_recover_start; scalar_t__ ls_recover_block; int ls_recover_size; int /*<<< orphan*/  ls_lvb_bits; int /*<<< orphan*/  ls_recover_spin; int /*<<< orphan*/  ls_recover_result; int /*<<< orphan*/  ls_recover_submit; int /*<<< orphan*/  ls_recover_flags; } ;
struct gfs2_sbd {struct lm_lockstruct sd_lockstruct; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFL_BLOCK_LOCKS ; 
 int /*<<< orphan*/  DFL_DLM_RECOVERY ; 
 int /*<<< orphan*/  DFL_FIRST_MOUNT ; 
 int /*<<< orphan*/  DFL_FIRST_MOUNT_DONE ; 
 int /*<<< orphan*/  DFL_MOUNT_DONE ; 
 int DLM_LKF_CONVERT ; 
 int DLM_LKF_VALBLK ; 
 int /*<<< orphan*/  DLM_LOCK_NL ; 
 int /*<<< orphan*/  DLM_LOCK_PR ; 
 int GDLM_LVB_SIZE ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int control_lock (struct gfs2_sbd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  control_lvb_write (struct lm_lockstruct*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  control_unlock (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,int,...) ; 
 int /*<<< orphan*/  fs_info (struct gfs2_sbd*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mounted_lock (struct gfs2_sbd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int control_first_done(struct gfs2_sbd *sdp)
{
	struct lm_lockstruct *ls = &sdp->sd_lockstruct;
	uint32_t start_gen, block_gen;
	int error;

restart:
	spin_lock(&ls->ls_recover_spin);
	start_gen = ls->ls_recover_start;
	block_gen = ls->ls_recover_block;

	if (test_bit(DFL_BLOCK_LOCKS, &ls->ls_recover_flags) ||
	    !test_bit(DFL_MOUNT_DONE, &ls->ls_recover_flags) ||
	    !test_bit(DFL_FIRST_MOUNT, &ls->ls_recover_flags)) {
		/* sanity check, should not happen */
		fs_err(sdp, "control_first_done start %u block %u flags %lx\n",
		       start_gen, block_gen, ls->ls_recover_flags);
		spin_unlock(&ls->ls_recover_spin);
		control_unlock(sdp);
		return -1;
	}

	if (start_gen == block_gen) {
		/*
		 * Wait for the end of a dlm recovery cycle to switch from
		 * first mounter recovery.  We can ignore any recover_slot
		 * callbacks between the recover_prep and next recover_done
		 * because we are still the first mounter and any failed nodes
		 * have not fully mounted, so they don't need recovery.
		 */
		spin_unlock(&ls->ls_recover_spin);
		fs_info(sdp, "control_first_done wait gen %u\n", start_gen);

		wait_on_bit(&ls->ls_recover_flags, DFL_DLM_RECOVERY,
			    TASK_UNINTERRUPTIBLE);
		goto restart;
	}

	clear_bit(DFL_FIRST_MOUNT, &ls->ls_recover_flags);
	set_bit(DFL_FIRST_MOUNT_DONE, &ls->ls_recover_flags);
	memset(ls->ls_recover_submit, 0, ls->ls_recover_size*sizeof(uint32_t));
	memset(ls->ls_recover_result, 0, ls->ls_recover_size*sizeof(uint32_t));
	spin_unlock(&ls->ls_recover_spin);

	memset(ls->ls_lvb_bits, 0, GDLM_LVB_SIZE);
	control_lvb_write(ls, start_gen, ls->ls_lvb_bits);

	error = mounted_lock(sdp, DLM_LOCK_PR, DLM_LKF_CONVERT);
	if (error)
		fs_err(sdp, "control_first_done mounted PR error %d\n", error);

	error = control_lock(sdp, DLM_LOCK_NL, DLM_LKF_CONVERT|DLM_LKF_VALBLK);
	if (error)
		fs_err(sdp, "control_first_done control NL error %d\n", error);

	return error;
}