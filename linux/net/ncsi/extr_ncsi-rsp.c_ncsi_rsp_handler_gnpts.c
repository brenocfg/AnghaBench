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
struct ncsi_rsp_gnpts_pkt {int /*<<< orphan*/  rx_os_err; int /*<<< orphan*/  rx_us_err; int /*<<< orphan*/  rx_channel_err; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_pkts; int /*<<< orphan*/  tx_us_err; int /*<<< orphan*/  tx_channel_err; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_pkts; TYPE_2__ rsp; } ;
struct ncsi_request {int /*<<< orphan*/  rsp; struct ncsi_dev_priv* ndp; } ;
struct ncsi_dev_priv {int dummy; } ;
struct ncsi_channel_stats {void* pt_rx_os_err; void* pt_rx_us_err; void* pt_rx_channel_err; void* pt_rx_dropped; void* pt_rx_pkts; void* pt_tx_us_err; void* pt_tx_channel_err; void* pt_tx_dropped; void* pt_tx_pkts; } ;
struct ncsi_channel {struct ncsi_channel_stats stats; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ncsi_find_package_and_channel (struct ncsi_dev_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ncsi_channel**) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_network_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ncsi_rsp_handler_gnpts(struct ncsi_request *nr)
{
	struct ncsi_rsp_gnpts_pkt *rsp;
	struct ncsi_dev_priv *ndp = nr->ndp;
	struct ncsi_channel *nc;
	struct ncsi_channel_stats *ncs;

	/* Find the channel */
	rsp = (struct ncsi_rsp_gnpts_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      NULL, &nc);
	if (!nc)
		return -ENODEV;

	/* Update HNC's statistics */
	ncs = &nc->stats;
	ncs->pt_tx_pkts        = ntohl(rsp->tx_pkts);
	ncs->pt_tx_dropped     = ntohl(rsp->tx_dropped);
	ncs->pt_tx_channel_err = ntohl(rsp->tx_channel_err);
	ncs->pt_tx_us_err      = ntohl(rsp->tx_us_err);
	ncs->pt_rx_pkts        = ntohl(rsp->rx_pkts);
	ncs->pt_rx_dropped     = ntohl(rsp->rx_dropped);
	ncs->pt_rx_channel_err = ntohl(rsp->rx_channel_err);
	ncs->pt_rx_us_err      = ntohl(rsp->rx_us_err);
	ncs->pt_rx_os_err      = ntohl(rsp->rx_os_err);

	return 0;
}