#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  status_buf_offset; int /*<<< orphan*/  status_buflen; int /*<<< orphan*/  status; } ;
struct TYPE_10__ {int /*<<< orphan*/  status; int /*<<< orphan*/  req_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  info_buf_offset; int /*<<< orphan*/  info_buflen; int /*<<< orphan*/  status; int /*<<< orphan*/  req_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  pkt_alignment_factor; int /*<<< orphan*/  max_pkt_per_msg; int /*<<< orphan*/  max_xfer_size; int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  minor_ver; int /*<<< orphan*/  major_ver; int /*<<< orphan*/  status; int /*<<< orphan*/  req_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  per_pkt_info_len; int /*<<< orphan*/  per_pkt_info_offset; int /*<<< orphan*/  oob_data_len; int /*<<< orphan*/  oob_data_offset; int /*<<< orphan*/  num_oob_data_elements; int /*<<< orphan*/  data_len; int /*<<< orphan*/  data_offset; } ;
struct TYPE_12__ {TYPE_5__ indicate_status; TYPE_4__ set_complete; TYPE_3__ query_complete; TYPE_2__ init_complete; TYPE_1__ pkt; } ;
struct rndis_message {int ndis_msg_type; int /*<<< orphan*/  msg_len; TYPE_6__ msg; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  RNDIS_MSG_INDICATE 132 
#define  RNDIS_MSG_INIT_C 131 
#define  RNDIS_MSG_PACKET 130 
#define  RNDIS_MSG_QUERY_C 129 
#define  RNDIS_MSG_SET_C 128 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void dump_rndis_message(struct net_device *netdev,
			       const struct rndis_message *rndis_msg)
{
	switch (rndis_msg->ndis_msg_type) {
	case RNDIS_MSG_PACKET:
		netdev_dbg(netdev, "RNDIS_MSG_PACKET (len %u, "
			   "data offset %u data len %u, # oob %u, "
			   "oob offset %u, oob len %u, pkt offset %u, "
			   "pkt len %u\n",
			   rndis_msg->msg_len,
			   rndis_msg->msg.pkt.data_offset,
			   rndis_msg->msg.pkt.data_len,
			   rndis_msg->msg.pkt.num_oob_data_elements,
			   rndis_msg->msg.pkt.oob_data_offset,
			   rndis_msg->msg.pkt.oob_data_len,
			   rndis_msg->msg.pkt.per_pkt_info_offset,
			   rndis_msg->msg.pkt.per_pkt_info_len);
		break;

	case RNDIS_MSG_INIT_C:
		netdev_dbg(netdev, "RNDIS_MSG_INIT_C "
			"(len %u, id 0x%x, status 0x%x, major %d, minor %d, "
			"device flags %d, max xfer size 0x%x, max pkts %u, "
			"pkt aligned %u)\n",
			rndis_msg->msg_len,
			rndis_msg->msg.init_complete.req_id,
			rndis_msg->msg.init_complete.status,
			rndis_msg->msg.init_complete.major_ver,
			rndis_msg->msg.init_complete.minor_ver,
			rndis_msg->msg.init_complete.dev_flags,
			rndis_msg->msg.init_complete.max_xfer_size,
			rndis_msg->msg.init_complete.
			   max_pkt_per_msg,
			rndis_msg->msg.init_complete.
			   pkt_alignment_factor);
		break;

	case RNDIS_MSG_QUERY_C:
		netdev_dbg(netdev, "RNDIS_MSG_QUERY_C "
			"(len %u, id 0x%x, status 0x%x, buf len %u, "
			"buf offset %u)\n",
			rndis_msg->msg_len,
			rndis_msg->msg.query_complete.req_id,
			rndis_msg->msg.query_complete.status,
			rndis_msg->msg.query_complete.
			   info_buflen,
			rndis_msg->msg.query_complete.
			   info_buf_offset);
		break;

	case RNDIS_MSG_SET_C:
		netdev_dbg(netdev,
			"RNDIS_MSG_SET_C (len %u, id 0x%x, status 0x%x)\n",
			rndis_msg->msg_len,
			rndis_msg->msg.set_complete.req_id,
			rndis_msg->msg.set_complete.status);
		break;

	case RNDIS_MSG_INDICATE:
		netdev_dbg(netdev, "RNDIS_MSG_INDICATE "
			"(len %u, status 0x%x, buf len %u, buf offset %u)\n",
			rndis_msg->msg_len,
			rndis_msg->msg.indicate_status.status,
			rndis_msg->msg.indicate_status.status_buflen,
			rndis_msg->msg.indicate_status.status_buf_offset);
		break;

	default:
		netdev_dbg(netdev, "0x%x (len %u)\n",
			rndis_msg->ndis_msg_type,
			rndis_msg->msg_len);
		break;
	}
}