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
struct rpmsg_device {int /*<<< orphan*/  ept; } ;
struct qcom_smd_endpoint {struct qcom_smd_channel* qsch; } ;
struct qcom_smd_channel {TYPE_1__* edge; int /*<<< orphan*/  recv_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  state_work; } ;

/* Variables and functions */
 int qcom_smd_channel_intr (struct qcom_smd_channel*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct qcom_smd_endpoint* to_smd_endpoint (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_smd_announce_create(struct rpmsg_device *rpdev)
{
	struct qcom_smd_endpoint *qept = to_smd_endpoint(rpdev->ept);
	struct qcom_smd_channel *channel = qept->qsch;
	unsigned long flags;
	bool kick_state;

	spin_lock_irqsave(&channel->recv_lock, flags);
	kick_state = qcom_smd_channel_intr(channel);
	spin_unlock_irqrestore(&channel->recv_lock, flags);

	if (kick_state)
		schedule_work(&channel->edge->state_work);

	return 0;
}