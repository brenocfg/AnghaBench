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
struct iscsi_login_rsp {int flags; } ;
struct iscsi_login_req {int /*<<< orphan*/  flags; } ;
struct iscsi_login {int login_complete; int /*<<< orphan*/  tsih; scalar_t__ rsp; scalar_t__ req; } ;
struct iscsi_conn {TYPE_1__* sess; } ;
struct TYPE_2__ {int /*<<< orphan*/  tsih; } ;

/* Variables and functions */
 int ISCSI_FLAG_LOGIN_CURRENT_STAGE1 ; 
 int ISCSI_FLAG_LOGIN_CURRENT_STAGE_MASK ; 
 int ISCSI_FLAG_LOGIN_NEXT_STAGE_MASK ; 
 int ISCSI_FLAG_LOGIN_TRANSIT ; 
 int ISCSI_LOGIN_CURRENT_STAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISCSI_LOGIN_STATUS_TARGET_ERROR ; 
 int /*<<< orphan*/  ISCSI_STATUS_CLS_TARGET_ERR ; 
 int MAX_LOGIN_PDUS ; 
 scalar_t__ iscsi_target_do_tx_login_io (struct iscsi_conn*,struct iscsi_login*) ; 
 int /*<<< orphan*/  iscsi_target_handle_csg_one (struct iscsi_conn*,struct iscsi_login*) ; 
 int /*<<< orphan*/  iscsi_target_handle_csg_zero (struct iscsi_conn*,struct iscsi_login*) ; 
 int /*<<< orphan*/  iscsi_target_restore_sock_callbacks (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsi_target_sk_check_close (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_tx_login_rsp (struct iscsi_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int iscsi_target_do_login(struct iscsi_conn *conn, struct iscsi_login *login)
{
	int pdu_count = 0;
	struct iscsi_login_req *login_req;
	struct iscsi_login_rsp *login_rsp;

	login_req = (struct iscsi_login_req *) login->req;
	login_rsp = (struct iscsi_login_rsp *) login->rsp;

	while (1) {
		if (++pdu_count > MAX_LOGIN_PDUS) {
			pr_err("MAX_LOGIN_PDUS count reached.\n");
			iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
					ISCSI_LOGIN_STATUS_TARGET_ERROR);
			return -1;
		}

		switch (ISCSI_LOGIN_CURRENT_STAGE(login_req->flags)) {
		case 0:
			login_rsp->flags &= ~ISCSI_FLAG_LOGIN_CURRENT_STAGE_MASK;
			if (iscsi_target_handle_csg_zero(conn, login) < 0)
				return -1;
			break;
		case 1:
			login_rsp->flags |= ISCSI_FLAG_LOGIN_CURRENT_STAGE1;
			if (iscsi_target_handle_csg_one(conn, login) < 0)
				return -1;
			if (login_rsp->flags & ISCSI_FLAG_LOGIN_TRANSIT) {
				/*
				 * Check to make sure the TCP connection has not
				 * dropped asynchronously while session reinstatement
				 * was occuring in this kthread context, before
				 * transitioning to full feature phase operation.
				 */
				if (iscsi_target_sk_check_close(conn))
					return -1;

				login->tsih = conn->sess->tsih;
				login->login_complete = 1;
				iscsi_target_restore_sock_callbacks(conn);
				if (iscsi_target_do_tx_login_io(conn,
						login) < 0)
					return -1;
				return 1;
			}
			break;
		default:
			pr_err("Illegal CSG: %d received from"
				" Initiator, protocol error.\n",
				ISCSI_LOGIN_CURRENT_STAGE(login_req->flags));
			break;
		}

		if (iscsi_target_do_tx_login_io(conn, login) < 0)
			return -1;

		if (login_rsp->flags & ISCSI_FLAG_LOGIN_TRANSIT) {
			login_rsp->flags &= ~ISCSI_FLAG_LOGIN_TRANSIT;
			login_rsp->flags &= ~ISCSI_FLAG_LOGIN_NEXT_STAGE_MASK;
		}
		break;
	}

	return 0;
}