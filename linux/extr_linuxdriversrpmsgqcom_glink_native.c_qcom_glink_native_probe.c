#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qcom_glink_pipe {int dummy; } ;
struct TYPE_5__ {int knows_txdone; struct device* dev; } ;
struct qcom_glink {unsigned long features; int intentless; int irq; int /*<<< orphan*/  mbox_chan; TYPE_3__ mbox_client; int /*<<< orphan*/  name; int /*<<< orphan*/  rcids; int /*<<< orphan*/  lcids; int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  rx_work; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  tx_lock; struct qcom_glink_pipe* rx_pipe; struct qcom_glink_pipe* tx_pipe; struct device* dev; } ;
struct device {TYPE_1__* of_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct qcom_glink* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct qcom_glink* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct qcom_glink* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int,char*,struct qcom_glink*) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbox_request_channel (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int of_irq_get (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int of_property_read_string (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_glink_native_intr ; 
 int qcom_glink_send_version (struct qcom_glink*) ; 
 int /*<<< orphan*/  qcom_glink_work ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct qcom_glink *qcom_glink_native_probe(struct device *dev,
					   unsigned long features,
					   struct qcom_glink_pipe *rx,
					   struct qcom_glink_pipe *tx,
					   bool intentless)
{
	int irq;
	int ret;
	struct qcom_glink *glink;

	glink = devm_kzalloc(dev, sizeof(*glink), GFP_KERNEL);
	if (!glink)
		return ERR_PTR(-ENOMEM);

	glink->dev = dev;
	glink->tx_pipe = tx;
	glink->rx_pipe = rx;

	glink->features = features;
	glink->intentless = intentless;

	spin_lock_init(&glink->tx_lock);
	spin_lock_init(&glink->rx_lock);
	INIT_LIST_HEAD(&glink->rx_queue);
	INIT_WORK(&glink->rx_work, qcom_glink_work);

	spin_lock_init(&glink->idr_lock);
	idr_init(&glink->lcids);
	idr_init(&glink->rcids);

	ret = of_property_read_string(dev->of_node, "label", &glink->name);
	if (ret < 0)
		glink->name = dev->of_node->name;

	glink->mbox_client.dev = dev;
	glink->mbox_client.knows_txdone = true;
	glink->mbox_chan = mbox_request_channel(&glink->mbox_client, 0);
	if (IS_ERR(glink->mbox_chan)) {
		if (PTR_ERR(glink->mbox_chan) != -EPROBE_DEFER)
			dev_err(dev, "failed to acquire IPC channel\n");
		return ERR_CAST(glink->mbox_chan);
	}

	irq = of_irq_get(dev->of_node, 0);
	ret = devm_request_irq(dev, irq,
			       qcom_glink_native_intr,
			       IRQF_NO_SUSPEND | IRQF_SHARED,
			       "glink-native", glink);
	if (ret) {
		dev_err(dev, "failed to request IRQ\n");
		return ERR_PTR(ret);
	}

	glink->irq = irq;

	ret = qcom_glink_send_version(glink);
	if (ret)
		return ERR_PTR(ret);

	return glink;
}