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
struct TYPE_3__ {int h_nodeid; } ;
struct dlm_message {int m_type; TYPE_1__ m_header; } ;
struct dlm_lkb {int lkb_nodeid; int /*<<< orphan*/  lkb_flags; int /*<<< orphan*/  lkb_remid; int /*<<< orphan*/  lkb_id; TYPE_2__* lkb_resource; } ;
struct TYPE_4__ {int /*<<< orphan*/  res_ls; } ;

/* Variables and functions */
#define  DLM_MSG_BAST 136 
#define  DLM_MSG_CANCEL 135 
#define  DLM_MSG_CANCEL_REPLY 134 
#define  DLM_MSG_CONVERT 133 
#define  DLM_MSG_CONVERT_REPLY 132 
#define  DLM_MSG_GRANT 131 
#define  DLM_MSG_REQUEST_REPLY 130 
#define  DLM_MSG_UNLOCK 129 
#define  DLM_MSG_UNLOCK_REPLY 128 
 int EINVAL ; 
 int /*<<< orphan*/  is_master_copy (struct dlm_lkb*) ; 
 int /*<<< orphan*/  is_process_copy (struct dlm_lkb*) ; 
 int /*<<< orphan*/  log_error (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int validate_message(struct dlm_lkb *lkb, struct dlm_message *ms)
{
	int from = ms->m_header.h_nodeid;
	int error = 0;

	switch (ms->m_type) {
	case DLM_MSG_CONVERT:
	case DLM_MSG_UNLOCK:
	case DLM_MSG_CANCEL:
		if (!is_master_copy(lkb) || lkb->lkb_nodeid != from)
			error = -EINVAL;
		break;

	case DLM_MSG_CONVERT_REPLY:
	case DLM_MSG_UNLOCK_REPLY:
	case DLM_MSG_CANCEL_REPLY:
	case DLM_MSG_GRANT:
	case DLM_MSG_BAST:
		if (!is_process_copy(lkb) || lkb->lkb_nodeid != from)
			error = -EINVAL;
		break;

	case DLM_MSG_REQUEST_REPLY:
		if (!is_process_copy(lkb))
			error = -EINVAL;
		else if (lkb->lkb_nodeid != -1 && lkb->lkb_nodeid != from)
			error = -EINVAL;
		break;

	default:
		error = -EINVAL;
	}

	if (error)
		log_error(lkb->lkb_resource->res_ls,
			  "ignore invalid message %d from %d %x %x %x %d",
			  ms->m_type, from, lkb->lkb_id, lkb->lkb_remid,
			  lkb->lkb_flags, lkb->lkb_nodeid);
	return error;
}