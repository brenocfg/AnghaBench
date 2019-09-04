#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct slim_msg_txn {int /*<<< orphan*/  mt; int /*<<< orphan*/  mc; int /*<<< orphan*/ * comp; } ;
struct slim_controller {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int qcom_slim_ngd_xfer_msg (struct slim_controller*,struct slim_msg_txn*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_slim_ngd_xfer_msg_sync(struct slim_controller *ctrl,
				       struct slim_msg_txn *txn)
{
	DECLARE_COMPLETION_ONSTACK(done);
	int ret, timeout;

	pm_runtime_get_sync(ctrl->dev);

	txn->comp = &done;

	ret = qcom_slim_ngd_xfer_msg(ctrl, txn);
	if (ret)
		return ret;

	timeout = wait_for_completion_timeout(&done, HZ);
	if (!timeout) {
		dev_err(ctrl->dev, "TX timed out:MC:0x%x,mt:0x%x", txn->mc,
				txn->mt);
		return -ETIMEDOUT;
	}
	return 0;
}