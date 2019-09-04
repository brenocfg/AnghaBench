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
struct qedi_endpoint {TYPE_1__* qedi; struct qedi_conn* conn; } ;
struct qedi_conn {int /*<<< orphan*/  qedi; } ;
struct iscsi_eqe_data {int /*<<< orphan*/  error_code; } ;
struct TYPE_2__ {int /*<<< orphan*/  dbg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedi_start_conn_recovery (int /*<<< orphan*/ ,struct qedi_conn*) ; 

void qedi_process_tcp_error(struct qedi_endpoint *ep,
			    struct iscsi_eqe_data *data)
{
	struct qedi_conn *qedi_conn;

	if (!ep)
		return;

	qedi_conn = ep->conn;
	if (!qedi_conn)
		return;

	QEDI_ERR(&ep->qedi->dbg_ctx, "async event TCP error:0x%x\n",
		 data->error_code);

	qedi_start_conn_recovery(qedi_conn->qedi, qedi_conn);
}