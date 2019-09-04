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
struct qcom_glink {int /*<<< orphan*/  dev; int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  lcids; } ;
struct glink_channel {int /*<<< orphan*/  open_ack; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct glink_channel* idr_find (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qcom_glink_rx_open_ack(struct qcom_glink *glink, unsigned int lcid)
{
	struct glink_channel *channel;

	spin_lock(&glink->idr_lock);
	channel = idr_find(&glink->lcids, lcid);
	spin_unlock(&glink->idr_lock);
	if (!channel) {
		dev_err(glink->dev, "Invalid open ack packet\n");
		return -EINVAL;
	}

	complete(&channel->open_ack);

	return 0;
}