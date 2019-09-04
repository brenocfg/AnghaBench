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
struct qcom_glink {int dummy; } ;
struct glink_channel {int /*<<< orphan*/  refcount; int /*<<< orphan*/  open_ack; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_glink_channel_release ; 
 int /*<<< orphan*/  qcom_glink_send_close_req (struct qcom_glink*,struct glink_channel*) ; 
 int /*<<< orphan*/  qcom_glink_send_open_ack (struct qcom_glink*,struct glink_channel*) ; 
 int qcom_glink_send_open_req (struct qcom_glink*,struct glink_channel*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int qcom_glink_create_remote(struct qcom_glink *glink,
				    struct glink_channel *channel)
{
	int ret;

	qcom_glink_send_open_ack(glink, channel);

	ret = qcom_glink_send_open_req(glink, channel);
	if (ret)
		goto close_link;

	ret = wait_for_completion_timeout(&channel->open_ack, 5 * HZ);
	if (!ret) {
		ret = -ETIMEDOUT;
		goto close_link;
	}

	return 0;

close_link:
	/*
	 * Send a close request to "undo" our open-ack. The close-ack will
	 * release the last reference.
	 */
	qcom_glink_send_close_req(glink, channel);

	/* Release qcom_glink_send_open_req() reference */
	kref_put(&channel->refcount, qcom_glink_channel_release);

	return ret;
}