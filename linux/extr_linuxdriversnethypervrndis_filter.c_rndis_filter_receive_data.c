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
typedef  scalar_t__ u32 ;
struct vmbus_channel {int dummy; } ;
struct rndis_packet {scalar_t__ data_offset; scalar_t__ data_len; } ;
struct TYPE_2__ {struct rndis_packet pkt; } ;
struct rndis_message {TYPE_1__ msg; } ;
struct netvsc_device {int dummy; } ;
struct net_device {int dummy; } ;
struct ndis_tcp_ip_checksum_info {int dummy; } ;
struct ndis_pkt_8021q_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE_8021Q_INFO ; 
 int NVSP_STAT_FAIL ; 
 scalar_t__ RNDIS_HEADER_SIZE ; 
 int /*<<< orphan*/  TCPIP_CHKSUM_PKTINFO ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,scalar_t__,scalar_t__) ; 
 int netvsc_recv_callback (struct net_device*,struct netvsc_device*,struct vmbus_channel*,void*,scalar_t__,struct ndis_tcp_ip_checksum_info const*,struct ndis_pkt_8021q_info const*) ; 
 void* rndis_get_ppi (struct rndis_packet*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rndis_filter_receive_data(struct net_device *ndev,
				     struct netvsc_device *nvdev,
				     struct vmbus_channel *channel,
				     struct rndis_message *msg,
				     u32 data_buflen)
{
	struct rndis_packet *rndis_pkt = &msg->msg.pkt;
	const struct ndis_tcp_ip_checksum_info *csum_info;
	const struct ndis_pkt_8021q_info *vlan;
	u32 data_offset;
	void *data;

	/* Remove the rndis header and pass it back up the stack */
	data_offset = RNDIS_HEADER_SIZE + rndis_pkt->data_offset;

	data_buflen -= data_offset;

	/*
	 * Make sure we got a valid RNDIS message, now total_data_buflen
	 * should be the data packet size plus the trailer padding size
	 */
	if (unlikely(data_buflen < rndis_pkt->data_len)) {
		netdev_err(ndev, "rndis message buffer "
			   "overflow detected (got %u, min %u)"
			   "...dropping this message!\n",
			   data_buflen, rndis_pkt->data_len);
		return NVSP_STAT_FAIL;
	}

	vlan = rndis_get_ppi(rndis_pkt, IEEE_8021Q_INFO);

	csum_info = rndis_get_ppi(rndis_pkt, TCPIP_CHKSUM_PKTINFO);

	data = (void *)msg + data_offset;

	/*
	 * Remove the rndis trailer padding from rndis packet message
	 * rndis_pkt->data_len tell us the real data length, we only copy
	 * the data packet to the stack, without the rndis trailer padding
	 */
	return netvsc_recv_callback(ndev, nvdev, channel,
				    data, rndis_pkt->data_len,
				    csum_info, vlan);
}