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
typedef  void* u8 ;
struct iscsi_login_rsp {int /*<<< orphan*/  itt; void* status_detail; void* status_class; int /*<<< orphan*/  opcode; } ;
struct iscsi_login {int login_failed; int /*<<< orphan*/ * rsp; } ;
struct iscsi_conn {TYPE_1__* conn_transport; int /*<<< orphan*/  login_itt; struct iscsi_login* conn_login; } ;
struct TYPE_2__ {int (* iscsit_put_login_tx ) (struct iscsi_conn*,struct iscsi_login*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_HDR_LEN ; 
 int /*<<< orphan*/  ISCSI_OP_LOGIN_RSP ; 
 int /*<<< orphan*/  iscsit_collect_login_stats (struct iscsi_conn*,void*,void*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct iscsi_conn*,struct iscsi_login*,int /*<<< orphan*/ ) ; 

int iscsit_tx_login_rsp(struct iscsi_conn *conn, u8 status_class, u8 status_detail)
{
	struct iscsi_login_rsp *hdr;
	struct iscsi_login *login = conn->conn_login;

	login->login_failed = 1;
	iscsit_collect_login_stats(conn, status_class, status_detail);

	memset(&login->rsp[0], 0, ISCSI_HDR_LEN);

	hdr	= (struct iscsi_login_rsp *)&login->rsp[0];
	hdr->opcode		= ISCSI_OP_LOGIN_RSP;
	hdr->status_class	= status_class;
	hdr->status_detail	= status_detail;
	hdr->itt		= conn->login_itt;

	return conn->conn_transport->iscsit_put_login_tx(conn, login, 0);
}