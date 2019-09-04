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
struct qcom_glink {scalar_t__ intentless; } ;
struct glink_core_rx_intent {int /*<<< orphan*/  node; int /*<<< orphan*/  id; int /*<<< orphan*/  reuse; struct glink_core_rx_intent* data; } ;
struct glink_channel {int /*<<< orphan*/  intent_work; int /*<<< orphan*/  intent_lock; int /*<<< orphan*/  done_intents; int /*<<< orphan*/  liids; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct glink_core_rx_intent*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qcom_glink_rx_done(struct qcom_glink *glink,
			       struct glink_channel *channel,
			       struct glink_core_rx_intent *intent)
{
	/* We don't send RX_DONE to intentless systems */
	if (glink->intentless) {
		kfree(intent->data);
		kfree(intent);
		return;
	}

	/* Take it off the tree of receive intents */
	if (!intent->reuse) {
		spin_lock(&channel->intent_lock);
		idr_remove(&channel->liids, intent->id);
		spin_unlock(&channel->intent_lock);
	}

	/* Schedule the sending of a rx_done indication */
	spin_lock(&channel->intent_lock);
	list_add_tail(&intent->node, &channel->done_intents);
	spin_unlock(&channel->intent_lock);

	schedule_work(&channel->intent_work);
}