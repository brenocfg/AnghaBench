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
struct TYPE_2__ {int h_nodeid; int h_length; } ;
struct dlm_rcom {int rc_id; int rc_result; int /*<<< orphan*/  rc_seq; int /*<<< orphan*/  rc_seq_reply; int /*<<< orphan*/  rc_buf; TYPE_1__ rc_header; } ;
struct dlm_mhandle {int dummy; } ;
struct dlm_ls {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LU_RECOVER_MASTER ; 
 int /*<<< orphan*/  DLM_RCOM_LOOKUP_REPLY ; 
 int create_rcom (struct dlm_ls*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_rcom**,struct dlm_mhandle**) ; 
 int /*<<< orphan*/  dlm_dump_rsb_name (struct dlm_ls*,int /*<<< orphan*/ ,int) ; 
 int dlm_master_lookup (struct dlm_ls*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,int) ; 
 int /*<<< orphan*/  send_rcom (struct dlm_ls*,struct dlm_mhandle*,struct dlm_rcom*) ; 

__attribute__((used)) static void receive_rcom_lookup(struct dlm_ls *ls, struct dlm_rcom *rc_in)
{
	struct dlm_rcom *rc;
	struct dlm_mhandle *mh;
	int error, ret_nodeid, nodeid = rc_in->rc_header.h_nodeid;
	int len = rc_in->rc_header.h_length - sizeof(struct dlm_rcom);

	error = create_rcom(ls, nodeid, DLM_RCOM_LOOKUP_REPLY, 0, &rc, &mh);
	if (error)
		return;

	/* Old code would send this special id to trigger a debug dump. */
	if (rc_in->rc_id == 0xFFFFFFFF) {
		log_error(ls, "receive_rcom_lookup dump from %d", nodeid);
		dlm_dump_rsb_name(ls, rc_in->rc_buf, len);
		return;
	}

	error = dlm_master_lookup(ls, nodeid, rc_in->rc_buf, len,
				  DLM_LU_RECOVER_MASTER, &ret_nodeid, NULL);
	if (error)
		ret_nodeid = error;
	rc->rc_result = ret_nodeid;
	rc->rc_id = rc_in->rc_id;
	rc->rc_seq_reply = rc_in->rc_seq;

	send_rcom(ls, mh, rc);
}