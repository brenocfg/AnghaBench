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
struct qcom_glink {int /*<<< orphan*/  rx_work; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  dev; } ;
struct glink_msg {int dummy; } ;
struct glink_defer_cmd {int /*<<< orphan*/  node; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct glink_defer_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_glink_rx_advance (struct qcom_glink*,int) ; 
 int qcom_glink_rx_avail (struct qcom_glink*) ; 
 int /*<<< orphan*/  qcom_glink_rx_peak (struct qcom_glink*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qcom_glink_rx_defer(struct qcom_glink *glink, size_t extra)
{
	struct glink_defer_cmd *dcmd;

	extra = ALIGN(extra, 8);

	if (qcom_glink_rx_avail(glink) < sizeof(struct glink_msg) + extra) {
		dev_dbg(glink->dev, "Insufficient data in rx fifo");
		return -ENXIO;
	}

	dcmd = kzalloc(sizeof(*dcmd) + extra, GFP_ATOMIC);
	if (!dcmd)
		return -ENOMEM;

	INIT_LIST_HEAD(&dcmd->node);

	qcom_glink_rx_peak(glink, &dcmd->msg, 0, sizeof(dcmd->msg) + extra);

	spin_lock(&glink->rx_lock);
	list_add_tail(&dcmd->node, &glink->rx_queue);
	spin_unlock(&glink->rx_lock);

	schedule_work(&glink->rx_work);
	qcom_glink_rx_advance(glink, sizeof(dcmd->msg) + extra);

	return 0;
}