#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {TYPE_1__ common; } ;
struct ncsi_rsp_gns_pkt {int /*<<< orphan*/  tx_aen_pkts; int /*<<< orphan*/  tx_pkts; int /*<<< orphan*/  rx_pkts; int /*<<< orphan*/  cmd_csum_errs; int /*<<< orphan*/  cmd_type_errs; int /*<<< orphan*/  dropped_cmds; int /*<<< orphan*/  rx_cmds; TYPE_2__ rsp; } ;
struct ncsi_request {int /*<<< orphan*/  rsp; struct ncsi_dev_priv* ndp; } ;
struct ncsi_dev_priv {int dummy; } ;
struct ncsi_channel_stats {void* ncsi_tx_aen_pkts; void* ncsi_tx_pkts; void* ncsi_rx_pkts; void* ncsi_cmd_csum_errs; void* ncsi_cmd_type_errs; void* ncsi_dropped_cmds; void* ncsi_rx_cmds; } ;
struct ncsi_channel {struct ncsi_channel_stats stats; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ncsi_find_package_and_channel (struct ncsi_dev_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ncsi_channel**) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_network_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ncsi_rsp_handler_gns(struct ncsi_request *nr)
{
	struct ncsi_rsp_gns_pkt *rsp;
	struct ncsi_dev_priv *ndp = nr->ndp;
	struct ncsi_channel *nc;
	struct ncsi_channel_stats *ncs;

	/* Find the channel */
	rsp = (struct ncsi_rsp_gns_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      NULL, &nc);
	if (!nc)
		return -ENODEV;

	/* Update HNC's statistics */
	ncs = &nc->stats;
	ncs->ncsi_rx_cmds       = ntohl(rsp->rx_cmds);
	ncs->ncsi_dropped_cmds  = ntohl(rsp->dropped_cmds);
	ncs->ncsi_cmd_type_errs = ntohl(rsp->cmd_type_errs);
	ncs->ncsi_cmd_csum_errs = ntohl(rsp->cmd_csum_errs);
	ncs->ncsi_rx_pkts       = ntohl(rsp->rx_pkts);
	ncs->ncsi_tx_pkts       = ntohl(rsp->tx_pkts);
	ncs->ncsi_tx_aen_pkts   = ntohl(rsp->tx_aen_pkts);

	return 0;
}