#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sbp_tport {struct sbp_tpg* tpg; } ;
struct sbp_tpg {int dummy; } ;
struct TYPE_6__ {void* status; } ;
struct TYPE_4__ {int /*<<< orphan*/  misc; } ;
struct sbp_management_request {scalar_t__ node_addr; TYPE_3__ status; TYPE_1__ orb; } ;
struct sbp_management_agent {struct sbp_tport* tport; } ;
struct sbp_login_descriptor {TYPE_2__* sess; int /*<<< orphan*/  login_id; int /*<<< orphan*/  login_lun; } ;
struct TYPE_5__ {scalar_t__ node_id; } ;

/* Variables and functions */
 int LOGOUT_ORB_LOGIN_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBP_STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  SBP_STATUS_LOGIN_ID_UNKNOWN ; 
 int /*<<< orphan*/  SBP_STATUS_OK ; 
 int STATUS_BLOCK_RESP (int /*<<< orphan*/ ) ; 
 int STATUS_BLOCK_SBP_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_RESP_REQUEST_COMPLETE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 struct sbp_login_descriptor* sbp_login_find_by_id (struct sbp_tpg*,int) ; 
 int /*<<< orphan*/  sbp_login_release (struct sbp_login_descriptor*,int) ; 

__attribute__((used)) static void sbp_management_request_logout(
	struct sbp_management_agent *agent, struct sbp_management_request *req,
	int *status_data_size)
{
	struct sbp_tport *tport = agent->tport;
	struct sbp_tpg *tpg = tport->tpg;
	int id;
	struct sbp_login_descriptor *login;

	id = LOGOUT_ORB_LOGIN_ID(be32_to_cpu(req->orb.misc));

	login = sbp_login_find_by_id(tpg, id);
	if (!login) {
		pr_warn("cannot find login: %d\n", id);

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_LOGIN_ID_UNKNOWN));
		return;
	}

	pr_info("mgt_agent LOGOUT from LUN %d session %d\n",
		login->login_lun, login->login_id);

	if (req->node_addr != login->sess->node_id) {
		pr_warn("logout from different node ID\n");

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_ACCESS_DENIED));
		return;
	}

	sbp_login_release(login, true);

	req->status.status = cpu_to_be32(
		STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
		STATUS_BLOCK_SBP_STATUS(SBP_STATUS_OK));
}