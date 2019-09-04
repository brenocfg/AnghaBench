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
struct rcom_lock {int rl_asts; scalar_t__ rl_wait_type; int /*<<< orphan*/  rl_status; int /*<<< orphan*/  rl_lvb; int /*<<< orphan*/  rl_grmode; int /*<<< orphan*/  rl_rqmode; int /*<<< orphan*/  rl_lvbseq; int /*<<< orphan*/  rl_flags; int /*<<< orphan*/  rl_exflags; int /*<<< orphan*/  rl_lkid; int /*<<< orphan*/  rl_ownpid; } ;
struct dlm_rsb {int dummy; } ;
struct TYPE_2__ {int h_length; int /*<<< orphan*/  h_nodeid; } ;
struct dlm_rcom {TYPE_1__ rc_header; scalar_t__ rc_buf; } ;
struct dlm_ls {int ls_lvblen; } ;
struct dlm_lkb {int lkb_ownpid; int lkb_remid; int lkb_exflags; int lkb_flags; int lkb_lvbseq; int /*<<< orphan*/  lkb_grmode; int /*<<< orphan*/  lkb_lvbptr; int /*<<< orphan*/ * lkb_astfn; int /*<<< orphan*/ * lkb_bastfn; int /*<<< orphan*/  lkb_rqmode; int /*<<< orphan*/  lkb_nodeid; } ;

/* Variables and functions */
 int DLM_CB_BAST ; 
 int DLM_CB_CAST ; 
 int DLM_IFL_MSTCPY ; 
 int DLM_LKF_VALBLK ; 
 int /*<<< orphan*/  DLM_LKSTS_CONVERT ; 
 int /*<<< orphan*/  DLM_LOCK_IV ; 
 int /*<<< orphan*/  DLM_MSG_CONVERT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RSB_RECOVER_CONVERT ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_allocate_lvb (struct dlm_ls*) ; 
 int /*<<< orphan*/  fake_astfn ; 
 int /*<<< orphan*/  fake_bastfn ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ middle_conversion (struct dlm_lkb*) ; 
 int /*<<< orphan*/  rsb_set_flag (struct dlm_rsb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int receive_rcom_lock_args(struct dlm_ls *ls, struct dlm_lkb *lkb,
				  struct dlm_rsb *r, struct dlm_rcom *rc)
{
	struct rcom_lock *rl = (struct rcom_lock *) rc->rc_buf;

	lkb->lkb_nodeid = rc->rc_header.h_nodeid;
	lkb->lkb_ownpid = le32_to_cpu(rl->rl_ownpid);
	lkb->lkb_remid = le32_to_cpu(rl->rl_lkid);
	lkb->lkb_exflags = le32_to_cpu(rl->rl_exflags);
	lkb->lkb_flags = le32_to_cpu(rl->rl_flags) & 0x0000FFFF;
	lkb->lkb_flags |= DLM_IFL_MSTCPY;
	lkb->lkb_lvbseq = le32_to_cpu(rl->rl_lvbseq);
	lkb->lkb_rqmode = rl->rl_rqmode;
	lkb->lkb_grmode = rl->rl_grmode;
	/* don't set lkb_status because add_lkb wants to itself */

	lkb->lkb_bastfn = (rl->rl_asts & DLM_CB_BAST) ? &fake_bastfn : NULL;
	lkb->lkb_astfn = (rl->rl_asts & DLM_CB_CAST) ? &fake_astfn : NULL;

	if (lkb->lkb_exflags & DLM_LKF_VALBLK) {
		int lvblen = rc->rc_header.h_length - sizeof(struct dlm_rcom) -
			 sizeof(struct rcom_lock);
		if (lvblen > ls->ls_lvblen)
			return -EINVAL;
		lkb->lkb_lvbptr = dlm_allocate_lvb(ls);
		if (!lkb->lkb_lvbptr)
			return -ENOMEM;
		memcpy(lkb->lkb_lvbptr, rl->rl_lvb, lvblen);
	}

	/* Conversions between PR and CW (middle modes) need special handling.
	   The real granted mode of these converting locks cannot be determined
	   until all locks have been rebuilt on the rsb (recover_conversion) */

	if (rl->rl_wait_type == cpu_to_le16(DLM_MSG_CONVERT) &&
	    middle_conversion(lkb)) {
		rl->rl_status = DLM_LKSTS_CONVERT;
		lkb->lkb_grmode = DLM_LOCK_IV;
		rsb_set_flag(r, RSB_RECOVER_CONVERT);
	}

	return 0;
}