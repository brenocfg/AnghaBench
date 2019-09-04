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
struct TYPE_3__ {int h_nodeid; int h_length; } ;
struct dlm_rcom {int /*<<< orphan*/  rc_buf; int /*<<< orphan*/  rc_seq; int /*<<< orphan*/  rc_seq_reply; int /*<<< orphan*/  rc_id; TYPE_1__ rc_header; } ;
struct dlm_mhandle {int dummy; } ;
struct dlm_ls {int dummy; } ;
struct TYPE_4__ {int ci_buffer_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_RCOM_NAMES_REPLY ; 
 int create_rcom (struct dlm_ls*,int,int /*<<< orphan*/ ,int,struct dlm_rcom**,struct dlm_mhandle**) ; 
 TYPE_2__ dlm_config ; 
 int /*<<< orphan*/  dlm_copy_master_names (struct dlm_ls*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  send_rcom (struct dlm_ls*,struct dlm_mhandle*,struct dlm_rcom*) ; 

__attribute__((used)) static void receive_rcom_names(struct dlm_ls *ls, struct dlm_rcom *rc_in)
{
	struct dlm_rcom *rc;
	struct dlm_mhandle *mh;
	int error, inlen, outlen, nodeid;

	nodeid = rc_in->rc_header.h_nodeid;
	inlen = rc_in->rc_header.h_length - sizeof(struct dlm_rcom);
	outlen = dlm_config.ci_buffer_size - sizeof(struct dlm_rcom);

	error = create_rcom(ls, nodeid, DLM_RCOM_NAMES_REPLY, outlen, &rc, &mh);
	if (error)
		return;
	rc->rc_id = rc_in->rc_id;
	rc->rc_seq_reply = rc_in->rc_seq;

	dlm_copy_master_names(ls, rc_in->rc_buf, inlen, rc->rc_buf, outlen,
			      nodeid);
	send_rcom(ls, mh, rc);
}