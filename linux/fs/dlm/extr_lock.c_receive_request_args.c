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
struct TYPE_2__ {int /*<<< orphan*/  h_nodeid; } ;
struct dlm_message {int m_asts; int /*<<< orphan*/  m_rqmode; int /*<<< orphan*/  m_lkid; int /*<<< orphan*/  m_pid; TYPE_1__ m_header; } ;
struct dlm_ls {int dummy; } ;
struct dlm_lkb {int lkb_exflags; int /*<<< orphan*/  lkb_lvbptr; int /*<<< orphan*/ * lkb_astfn; int /*<<< orphan*/ * lkb_bastfn; int /*<<< orphan*/  lkb_rqmode; int /*<<< orphan*/  lkb_grmode; int /*<<< orphan*/  lkb_remid; int /*<<< orphan*/  lkb_ownpid; int /*<<< orphan*/  lkb_nodeid; } ;

/* Variables and functions */
 int DLM_CB_BAST ; 
 int DLM_CB_CAST ; 
 int DLM_LKF_VALBLK ; 
 int /*<<< orphan*/  DLM_LOCK_IV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dlm_allocate_lvb (struct dlm_ls*) ; 
 int /*<<< orphan*/  fake_astfn ; 
 int /*<<< orphan*/  fake_bastfn ; 

__attribute__((used)) static int receive_request_args(struct dlm_ls *ls, struct dlm_lkb *lkb,
				struct dlm_message *ms)
{
	lkb->lkb_nodeid = ms->m_header.h_nodeid;
	lkb->lkb_ownpid = ms->m_pid;
	lkb->lkb_remid = ms->m_lkid;
	lkb->lkb_grmode = DLM_LOCK_IV;
	lkb->lkb_rqmode = ms->m_rqmode;

	lkb->lkb_bastfn = (ms->m_asts & DLM_CB_BAST) ? &fake_bastfn : NULL;
	lkb->lkb_astfn = (ms->m_asts & DLM_CB_CAST) ? &fake_astfn : NULL;

	if (lkb->lkb_exflags & DLM_LKF_VALBLK) {
		/* lkb was just created so there won't be an lvb yet */
		lkb->lkb_lvbptr = dlm_allocate_lvb(ls);
		if (!lkb->lkb_lvbptr)
			return -ENOMEM;
	}

	return 0;
}