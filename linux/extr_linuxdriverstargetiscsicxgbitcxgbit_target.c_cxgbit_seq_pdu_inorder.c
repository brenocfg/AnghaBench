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
struct iscsi_param {int /*<<< orphan*/  value; } ;
struct iscsi_conn {TYPE_2__* sess; int /*<<< orphan*/  param_list; TYPE_3__* login; } ;
struct cxgbit_sock {struct iscsi_conn* conn; } ;
struct TYPE_6__ {scalar_t__ leading_connection; } ;
struct TYPE_5__ {TYPE_1__* sess_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  DataPDUInOrder; int /*<<< orphan*/  DataSequenceInOrder; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATAPDUINORDER ; 
 int /*<<< orphan*/  DATASEQUENCEINORDER ; 
 int /*<<< orphan*/  YES ; 
 struct iscsi_param* iscsi_find_param_from_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxgbit_seq_pdu_inorder(struct cxgbit_sock *csk)
{
	struct iscsi_conn *conn = csk->conn;
	struct iscsi_param *param;

	if (conn->login->leading_connection) {
		param = iscsi_find_param_from_key(DATASEQUENCEINORDER,
						  conn->param_list);
		if (!param) {
			pr_err("param not found key %s\n", DATASEQUENCEINORDER);
			return -1;
		}

		if (strcmp(param->value, YES))
			return 1;

		param = iscsi_find_param_from_key(DATAPDUINORDER,
						  conn->param_list);
		if (!param) {
			pr_err("param not found key %s\n", DATAPDUINORDER);
			return -1;
		}

		if (strcmp(param->value, YES))
			return 1;

	} else {
		if (!conn->sess->sess_ops->DataSequenceInOrder)
			return 1;
		if (!conn->sess->sess_ops->DataPDUInOrder)
			return 1;
	}

	return 0;
}