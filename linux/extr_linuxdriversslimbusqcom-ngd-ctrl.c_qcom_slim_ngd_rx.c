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
typedef  scalar_t__ u8 ;
struct qcom_slim_ngd_ctrl {int /*<<< orphan*/  dev; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  m_work; int /*<<< orphan*/  mwq; } ;

/* Variables and functions */
 scalar_t__ SLIM_HEADER_GET_MC (scalar_t__) ; 
 scalar_t__ SLIM_HEADER_GET_MT (scalar_t__) ; 
 scalar_t__ SLIM_HEADER_GET_RL (scalar_t__) ; 
 scalar_t__ SLIM_MSG_MC_REPLY_INFORMATION ; 
 scalar_t__ SLIM_MSG_MC_REPLY_VALUE ; 
 scalar_t__ SLIM_MSG_MT_SRC_REFERRED_USER ; 
 scalar_t__ SLIM_USR_MC_ADDR_REPLY ; 
 scalar_t__ SLIM_USR_MC_GENERIC_ACK ; 
 scalar_t__ SLIM_USR_MC_MASTER_CAPABILITY ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slim_msg_response (int /*<<< orphan*/ *,scalar_t__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void qcom_slim_ngd_rx(struct qcom_slim_ngd_ctrl *ctrl, u8 *buf)
{
	u8 mc, mt, len;

	mt = SLIM_HEADER_GET_MT(buf[0]);
	len = SLIM_HEADER_GET_RL(buf[0]);
	mc = SLIM_HEADER_GET_MC(buf[1]);

	if (mc == SLIM_USR_MC_MASTER_CAPABILITY &&
		mt == SLIM_MSG_MT_SRC_REFERRED_USER)
		queue_work(ctrl->mwq, &ctrl->m_work);

	if (mc == SLIM_MSG_MC_REPLY_INFORMATION ||
	    mc == SLIM_MSG_MC_REPLY_VALUE || (mc == SLIM_USR_MC_ADDR_REPLY &&
	    mt == SLIM_MSG_MT_SRC_REFERRED_USER) ||
		(mc == SLIM_USR_MC_GENERIC_ACK &&
		 mt == SLIM_MSG_MT_SRC_REFERRED_USER)) {
		slim_msg_response(&ctrl->ctrl, &buf[4], buf[3], len - 4);
		pm_runtime_mark_last_busy(ctrl->dev);
	}
}