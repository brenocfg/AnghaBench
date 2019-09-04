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
struct qcom_glink {int /*<<< orphan*/  dev; int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  rcids; } ;
struct glink_channel {int intent_req_result; int /*<<< orphan*/  intent_req_comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct glink_channel* idr_find (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qcom_glink_handle_intent_req_ack(struct qcom_glink *glink,
					     unsigned int cid, bool granted)
{
	struct glink_channel *channel;
	unsigned long flags;

	spin_lock_irqsave(&glink->idr_lock, flags);
	channel = idr_find(&glink->rcids, cid);
	spin_unlock_irqrestore(&glink->idr_lock, flags);
	if (!channel) {
		dev_err(glink->dev, "unable to find channel\n");
		return;
	}

	channel->intent_req_result = granted;
	complete(&channel->intent_req_comp);
}