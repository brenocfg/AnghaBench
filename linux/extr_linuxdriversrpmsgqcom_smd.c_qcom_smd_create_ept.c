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
struct rpmsg_endpoint {int /*<<< orphan*/  refcount; int /*<<< orphan*/ * ops; void* priv; int /*<<< orphan*/  cb; struct rpmsg_device* rpdev; } ;
struct rpmsg_device {int /*<<< orphan*/  dev; } ;
struct rpmsg_channel_info {char* name; } ;
struct qcom_smd_endpoint {struct qcom_smd_channel* qsch; struct rpmsg_endpoint ept; } ;
struct qcom_smd_edge {int /*<<< orphan*/  new_channel_event; } ;
struct qcom_smd_device {struct qcom_smd_edge* edge; } ;
struct qcom_smd_channel {scalar_t__ state; struct qcom_smd_endpoint* qsept; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  rpmsg_rx_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 scalar_t__ SMD_CHANNEL_CLOSED ; 
 int /*<<< orphan*/  __ept_release ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct qcom_smd_endpoint* kzalloc (int,int /*<<< orphan*/ ) ; 
 int qcom_smd_channel_open (struct qcom_smd_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_smd_endpoint_ops ; 
 struct qcom_smd_channel* qcom_smd_find_channel (struct qcom_smd_edge*,char const*) ; 
 struct qcom_smd_device* to_smd_device (struct rpmsg_device*) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rpmsg_endpoint *qcom_smd_create_ept(struct rpmsg_device *rpdev,
						  rpmsg_rx_cb_t cb, void *priv,
						  struct rpmsg_channel_info chinfo)
{
	struct qcom_smd_endpoint *qsept;
	struct qcom_smd_channel *channel;
	struct qcom_smd_device *qsdev = to_smd_device(rpdev);
	struct qcom_smd_edge *edge = qsdev->edge;
	struct rpmsg_endpoint *ept;
	const char *name = chinfo.name;
	int ret;

	/* Wait up to HZ for the channel to appear */
	ret = wait_event_interruptible_timeout(edge->new_channel_event,
			(channel = qcom_smd_find_channel(edge, name)) != NULL,
			HZ);
	if (!ret)
		return NULL;

	if (channel->state != SMD_CHANNEL_CLOSED) {
		dev_err(&rpdev->dev, "channel %s is busy\n", channel->name);
		return NULL;
	}

	qsept = kzalloc(sizeof(*qsept), GFP_KERNEL);
	if (!qsept)
		return NULL;

	ept = &qsept->ept;

	kref_init(&ept->refcount);

	ept->rpdev = rpdev;
	ept->cb = cb;
	ept->priv = priv;
	ept->ops = &qcom_smd_endpoint_ops;

	channel->qsept = qsept;
	qsept->qsch = channel;

	ret = qcom_smd_channel_open(channel, cb);
	if (ret)
		goto free_ept;

	return ept;

free_ept:
	channel->qsept = NULL;
	kref_put(&ept->refcount, __ept_release);
	return NULL;
}