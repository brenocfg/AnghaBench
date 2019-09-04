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
struct TYPE_2__ {scalar_t__ result; } ;
struct test_ping_resp_msg_v01 {int /*<<< orphan*/  pong; int /*<<< orphan*/  pong_valid; TYPE_1__ resp; } ;
struct sockaddr_qrtr {int dummy; } ;
struct qmi_txn {int /*<<< orphan*/  completion; int /*<<< orphan*/  result; } ;
struct qmi_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 scalar_t__ QMI_RESULT_FAILURE_V01 ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void ping_pong_cb(struct qmi_handle *qmi, struct sockaddr_qrtr *sq,
			 struct qmi_txn *txn, const void *data)
{
	const struct test_ping_resp_msg_v01 *resp = data;

	if (!txn) {
		pr_err("spurious ping response\n");
		return;
	}

	if (resp->resp.result == QMI_RESULT_FAILURE_V01)
		txn->result = -ENXIO;
	else if (!resp->pong_valid || memcmp(resp->pong, "pong", 4))
		txn->result = -EINVAL;

	complete(&txn->completion);
}