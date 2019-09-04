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
struct rpmsg_endpoint {int (* cb ) (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  priv; int /*<<< orphan*/  rpdev; } ;
struct qcom_smd_channel {unsigned int pkt_size; unsigned int fifo_size; void* rx_fifo; void* bounce_buffer; TYPE_1__* qsept; } ;
struct TYPE_2__ {struct rpmsg_endpoint ept; } ;

/* Variables and functions */
 unsigned int GET_RX_CHANNEL_INFO (struct qcom_smd_channel*,unsigned int) ; 
 int /*<<< orphan*/  RPMSG_ADDR_ANY ; 
 int /*<<< orphan*/  qcom_smd_channel_advance (struct qcom_smd_channel*,size_t) ; 
 size_t qcom_smd_channel_peek (struct qcom_smd_channel*,void*,unsigned int) ; 
 int stub1 (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_smd_channel_recv_single(struct qcom_smd_channel *channel)
{
	struct rpmsg_endpoint *ept = &channel->qsept->ept;
	unsigned tail;
	size_t len;
	void *ptr;
	int ret;

	tail = GET_RX_CHANNEL_INFO(channel, tail);

	/* Use bounce buffer if the data wraps */
	if (tail + channel->pkt_size >= channel->fifo_size) {
		ptr = channel->bounce_buffer;
		len = qcom_smd_channel_peek(channel, ptr, channel->pkt_size);
	} else {
		ptr = channel->rx_fifo + tail;
		len = channel->pkt_size;
	}

	ret = ept->cb(ept->rpdev, ptr, len, ept->priv, RPMSG_ADDR_ANY);
	if (ret < 0)
		return ret;

	/* Only forward the tail if the client consumed the data */
	qcom_smd_channel_advance(channel, len);

	channel->pkt_size = 0;

	return 0;
}