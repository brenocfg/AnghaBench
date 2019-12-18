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
struct rcom_lock {int /*<<< orphan*/  rl_lvb; int /*<<< orphan*/  rl_name; void* rl_namelen; int /*<<< orphan*/  rl_asts; void* rl_wait_type; int /*<<< orphan*/  rl_status; int /*<<< orphan*/  rl_grmode; int /*<<< orphan*/  rl_rqmode; void* rl_lvbseq; void* rl_flags; void* rl_exflags; void* rl_lkid; void* rl_ownpid; } ;
struct dlm_rsb {TYPE_1__* res_ls; int /*<<< orphan*/  res_length; scalar_t__ res_name; } ;
struct dlm_lkb {scalar_t__ lkb_lvbptr; scalar_t__ lkb_astfn; scalar_t__ lkb_bastfn; int /*<<< orphan*/  lkb_wait_type; int /*<<< orphan*/  lkb_status; int /*<<< orphan*/  lkb_grmode; int /*<<< orphan*/  lkb_rqmode; int /*<<< orphan*/  lkb_lvbseq; int /*<<< orphan*/  lkb_flags; int /*<<< orphan*/  lkb_exflags; int /*<<< orphan*/  lkb_id; int /*<<< orphan*/  lkb_ownpid; } ;
struct TYPE_2__ {int /*<<< orphan*/  ls_lvblen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_CB_BAST ; 
 int /*<<< orphan*/  DLM_CB_CAST ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rcom_lock*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pack_rcom_lock(struct dlm_rsb *r, struct dlm_lkb *lkb,
			   struct rcom_lock *rl)
{
	memset(rl, 0, sizeof(*rl));

	rl->rl_ownpid = cpu_to_le32(lkb->lkb_ownpid);
	rl->rl_lkid = cpu_to_le32(lkb->lkb_id);
	rl->rl_exflags = cpu_to_le32(lkb->lkb_exflags);
	rl->rl_flags = cpu_to_le32(lkb->lkb_flags);
	rl->rl_lvbseq = cpu_to_le32(lkb->lkb_lvbseq);
	rl->rl_rqmode = lkb->lkb_rqmode;
	rl->rl_grmode = lkb->lkb_grmode;
	rl->rl_status = lkb->lkb_status;
	rl->rl_wait_type = cpu_to_le16(lkb->lkb_wait_type);

	if (lkb->lkb_bastfn)
		rl->rl_asts |= DLM_CB_BAST;
	if (lkb->lkb_astfn)
		rl->rl_asts |= DLM_CB_CAST;

	rl->rl_namelen = cpu_to_le16(r->res_length);
	memcpy(rl->rl_name, r->res_name, r->res_length);

	/* FIXME: might we have an lvb without DLM_LKF_VALBLK set ?
	   If so, receive_rcom_lock_args() won't take this copy. */

	if (lkb->lkb_lvbptr)
		memcpy(rl->rl_lvb, lkb->lkb_lvbptr, r->res_ls->ls_lvblen);
}