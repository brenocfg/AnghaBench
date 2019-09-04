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
struct qcom_glink {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  lcids; } ;
struct glink_channel {int /*<<< orphan*/  refcount; int /*<<< orphan*/  lcid; int /*<<< orphan*/  open_req; int /*<<< orphan*/  open_ack; } ;

/* Variables and functions */
 struct glink_channel* ERR_CAST (struct glink_channel*) ; 
 struct glink_channel* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct glink_channel*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct glink_channel* qcom_glink_alloc_channel (struct qcom_glink*,char const*) ; 
 int /*<<< orphan*/  qcom_glink_channel_release ; 
 int /*<<< orphan*/  qcom_glink_send_open_ack (struct qcom_glink*,struct glink_channel*) ; 
 int qcom_glink_send_open_req (struct qcom_glink*,struct glink_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct glink_channel *qcom_glink_create_local(struct qcom_glink *glink,
						     const char *name)
{
	struct glink_channel *channel;
	int ret;
	unsigned long flags;

	channel = qcom_glink_alloc_channel(glink, name);
	if (IS_ERR(channel))
		return ERR_CAST(channel);

	ret = qcom_glink_send_open_req(glink, channel);
	if (ret)
		goto release_channel;

	ret = wait_for_completion_timeout(&channel->open_ack, 5 * HZ);
	if (!ret)
		goto err_timeout;

	ret = wait_for_completion_timeout(&channel->open_req, 5 * HZ);
	if (!ret)
		goto err_timeout;

	qcom_glink_send_open_ack(glink, channel);

	return channel;

err_timeout:
	/* qcom_glink_send_open_req() did register the channel in lcids*/
	spin_lock_irqsave(&glink->idr_lock, flags);
	idr_remove(&glink->lcids, channel->lcid);
	spin_unlock_irqrestore(&glink->idr_lock, flags);

release_channel:
	/* Release qcom_glink_send_open_req() reference */
	kref_put(&channel->refcount, qcom_glink_channel_release);
	/* Release qcom_glink_alloc_channel() reference */
	kref_put(&channel->refcount, qcom_glink_channel_release);

	return ERR_PTR(-ETIMEDOUT);
}