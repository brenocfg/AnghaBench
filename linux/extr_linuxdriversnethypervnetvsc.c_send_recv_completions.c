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
typedef  int /*<<< orphan*/  u32 ;
struct recv_comp_data {int /*<<< orphan*/  tid; int /*<<< orphan*/  status; } ;
struct nvsp_message_header {int /*<<< orphan*/  msg_type; } ;
struct netvsc_device {scalar_t__ recv_completion_cnt; int destroy; int /*<<< orphan*/  wait_drain; } ;
struct multi_recv_comp {scalar_t__ first; scalar_t__ next; struct recv_comp_data* slots; } ;
struct netvsc_channel {int /*<<< orphan*/  channel; struct multi_recv_comp mrc; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_comp_busy; } ;
struct net_device_context {TYPE_1__ eth_stats; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  NVSP_MSG1_TYPE_SEND_RNDIS_PKT_COMPLETE ; 
 int /*<<< orphan*/  VM_PKT_COMP ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 
 int vmbus_sendpacket (int /*<<< orphan*/ ,struct recv_comp_msg*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int send_recv_completions(struct net_device *ndev,
				 struct netvsc_device *nvdev,
				 struct netvsc_channel *nvchan)
{
	struct multi_recv_comp *mrc = &nvchan->mrc;
	struct recv_comp_msg {
		struct nvsp_message_header hdr;
		u32 status;
	}  __packed;
	struct recv_comp_msg msg = {
		.hdr.msg_type = NVSP_MSG1_TYPE_SEND_RNDIS_PKT_COMPLETE,
	};
	int ret;

	while (mrc->first != mrc->next) {
		const struct recv_comp_data *rcd
			= mrc->slots + mrc->first;

		msg.status = rcd->status;
		ret = vmbus_sendpacket(nvchan->channel, &msg, sizeof(msg),
				       rcd->tid, VM_PKT_COMP, 0);
		if (unlikely(ret)) {
			struct net_device_context *ndev_ctx = netdev_priv(ndev);

			++ndev_ctx->eth_stats.rx_comp_busy;
			return ret;
		}

		if (++mrc->first == nvdev->recv_completion_cnt)
			mrc->first = 0;
	}

	/* receive completion ring has been emptied */
	if (unlikely(nvdev->destroy))
		wake_up(&nvdev->wait_drain);

	return 0;
}