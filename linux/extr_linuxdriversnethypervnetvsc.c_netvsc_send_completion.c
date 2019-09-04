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
struct vmpacket_descriptor {int dummy; } ;
struct vmbus_channel {int dummy; } ;
struct TYPE_2__ {int msg_type; } ;
struct nvsp_message {TYPE_1__ hdr; } ;
struct netvsc_device {int /*<<< orphan*/  channel_init_wait; int /*<<< orphan*/  channel_init_pkt; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  NVSP_MSG1_TYPE_SEND_RECV_BUF_COMPLETE 132 
#define  NVSP_MSG1_TYPE_SEND_RNDIS_PKT_COMPLETE 131 
#define  NVSP_MSG1_TYPE_SEND_SEND_BUF_COMPLETE 130 
#define  NVSP_MSG5_TYPE_SUBCHANNEL 129 
#define  NVSP_MSG_TYPE_INIT_COMPLETE 128 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct nvsp_message* hv_pkt_data (struct vmpacket_descriptor const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct nvsp_message const*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netvsc_send_tx_complete (struct net_device*,struct netvsc_device*,struct vmbus_channel*,struct vmpacket_descriptor const*,int) ; 

__attribute__((used)) static void netvsc_send_completion(struct net_device *ndev,
				   struct netvsc_device *net_device,
				   struct vmbus_channel *incoming_channel,
				   const struct vmpacket_descriptor *desc,
				   int budget)
{
	const struct nvsp_message *nvsp_packet = hv_pkt_data(desc);

	switch (nvsp_packet->hdr.msg_type) {
	case NVSP_MSG_TYPE_INIT_COMPLETE:
	case NVSP_MSG1_TYPE_SEND_RECV_BUF_COMPLETE:
	case NVSP_MSG1_TYPE_SEND_SEND_BUF_COMPLETE:
	case NVSP_MSG5_TYPE_SUBCHANNEL:
		/* Copy the response back */
		memcpy(&net_device->channel_init_pkt, nvsp_packet,
		       sizeof(struct nvsp_message));
		complete(&net_device->channel_init_wait);
		break;

	case NVSP_MSG1_TYPE_SEND_RNDIS_PKT_COMPLETE:
		netvsc_send_tx_complete(ndev, net_device, incoming_channel,
					desc, budget);
		break;

	default:
		netdev_err(ndev,
			   "Unknown send completion type %d received!!\n",
			   nvsp_packet->hdr.msg_type);
	}
}