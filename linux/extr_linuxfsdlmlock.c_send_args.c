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
struct dlm_rsb {TYPE_1__* res_ls; int /*<<< orphan*/  res_length; int /*<<< orphan*/  res_name; int /*<<< orphan*/  res_hash; } ;
struct dlm_message {int m_type; int /*<<< orphan*/  m_extra; int /*<<< orphan*/  m_asts; int /*<<< orphan*/  m_hash; int /*<<< orphan*/  m_rqmode; int /*<<< orphan*/  m_grmode; int /*<<< orphan*/  m_status; int /*<<< orphan*/  m_lvbseq; int /*<<< orphan*/  m_flags; int /*<<< orphan*/  m_sbflags; int /*<<< orphan*/  m_exflags; int /*<<< orphan*/  m_remid; int /*<<< orphan*/  m_lkid; int /*<<< orphan*/  m_pid; int /*<<< orphan*/  m_nodeid; } ;
struct dlm_lkb {int /*<<< orphan*/  lkb_lvbptr; scalar_t__ lkb_astfn; scalar_t__ lkb_bastfn; int /*<<< orphan*/  lkb_rqmode; int /*<<< orphan*/  lkb_grmode; int /*<<< orphan*/  lkb_status; int /*<<< orphan*/  lkb_lvbseq; int /*<<< orphan*/  lkb_flags; int /*<<< orphan*/  lkb_sbflags; int /*<<< orphan*/  lkb_exflags; int /*<<< orphan*/  lkb_remid; int /*<<< orphan*/  lkb_id; int /*<<< orphan*/  lkb_ownpid; int /*<<< orphan*/  lkb_nodeid; } ;
struct TYPE_2__ {int /*<<< orphan*/  ls_lvblen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_CB_BAST ; 
 int /*<<< orphan*/  DLM_CB_CAST ; 
#define  DLM_MSG_CONVERT 134 
#define  DLM_MSG_CONVERT_REPLY 133 
#define  DLM_MSG_GRANT 132 
#define  DLM_MSG_LOOKUP 131 
#define  DLM_MSG_REQUEST 130 
#define  DLM_MSG_REQUEST_REPLY 129 
#define  DLM_MSG_UNLOCK 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_args(struct dlm_rsb *r, struct dlm_lkb *lkb,
		      struct dlm_message *ms)
{
	ms->m_nodeid   = lkb->lkb_nodeid;
	ms->m_pid      = lkb->lkb_ownpid;
	ms->m_lkid     = lkb->lkb_id;
	ms->m_remid    = lkb->lkb_remid;
	ms->m_exflags  = lkb->lkb_exflags;
	ms->m_sbflags  = lkb->lkb_sbflags;
	ms->m_flags    = lkb->lkb_flags;
	ms->m_lvbseq   = lkb->lkb_lvbseq;
	ms->m_status   = lkb->lkb_status;
	ms->m_grmode   = lkb->lkb_grmode;
	ms->m_rqmode   = lkb->lkb_rqmode;
	ms->m_hash     = r->res_hash;

	/* m_result and m_bastmode are set from function args,
	   not from lkb fields */

	if (lkb->lkb_bastfn)
		ms->m_asts |= DLM_CB_BAST;
	if (lkb->lkb_astfn)
		ms->m_asts |= DLM_CB_CAST;

	/* compare with switch in create_message; send_remove() doesn't
	   use send_args() */

	switch (ms->m_type) {
	case DLM_MSG_REQUEST:
	case DLM_MSG_LOOKUP:
		memcpy(ms->m_extra, r->res_name, r->res_length);
		break;
	case DLM_MSG_CONVERT:
	case DLM_MSG_UNLOCK:
	case DLM_MSG_REQUEST_REPLY:
	case DLM_MSG_CONVERT_REPLY:
	case DLM_MSG_GRANT:
		if (!lkb->lkb_lvbptr)
			break;
		memcpy(ms->m_extra, lkb->lkb_lvbptr, r->res_ls->ls_lvblen);
		break;
	}
}