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
struct rcom_lock {int dummy; } ;
struct TYPE_2__ {int h_nodeid; } ;
struct dlm_rcom {int /*<<< orphan*/  rc_seq; int /*<<< orphan*/  rc_seq_reply; int /*<<< orphan*/  rc_id; int /*<<< orphan*/  rc_buf; TYPE_1__ rc_header; } ;
struct dlm_mhandle {int dummy; } ;
struct dlm_ls {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_RCOM_LOCK_REPLY ; 
 int create_rcom (struct dlm_ls*,int,int /*<<< orphan*/ ,int,struct dlm_rcom**,struct dlm_mhandle**) ; 
 int /*<<< orphan*/  dlm_recover_master_copy (struct dlm_ls*,struct dlm_rcom*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_rcom (struct dlm_ls*,struct dlm_mhandle*,struct dlm_rcom*) ; 

__attribute__((used)) static void receive_rcom_lock(struct dlm_ls *ls, struct dlm_rcom *rc_in)
{
	struct dlm_rcom *rc;
	struct dlm_mhandle *mh;
	int error, nodeid = rc_in->rc_header.h_nodeid;

	dlm_recover_master_copy(ls, rc_in);

	error = create_rcom(ls, nodeid, DLM_RCOM_LOCK_REPLY,
			    sizeof(struct rcom_lock), &rc, &mh);
	if (error)
		return;

	/* We send back the same rcom_lock struct we received, but
	   dlm_recover_master_copy() has filled in rl_remid and rl_result */

	memcpy(rc->rc_buf, rc_in->rc_buf, sizeof(struct rcom_lock));
	rc->rc_id = rc_in->rc_id;
	rc->rc_seq_reply = rc_in->rc_seq;

	send_rcom(ls, mh, rc);
}