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
struct ncsi_rsp_pkt {TYPE_2__ rsp; } ;
struct ncsi_request {int /*<<< orphan*/  cmd; int /*<<< orphan*/  rsp; struct ncsi_dev_priv* ndp; } ;
struct ncsi_dev_priv {int dummy; } ;
struct ncsi_cmd_sma_pkt {int at_e; int index; int /*<<< orphan*/  mac; } ;
struct ncsi_channel_mac_filter {int n_uc; int n_mc; int n_mixed; int /*<<< orphan*/ * addrs; int /*<<< orphan*/  bitmap; } ;
struct ncsi_channel {int /*<<< orphan*/  lock; struct ncsi_channel_mac_filter mac_filter; } ;

/* Variables and functions */
 int ENODEV ; 
 int ERANGE ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  clear_bit (int,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ncsi_find_package_and_channel (struct ncsi_dev_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ncsi_channel**) ; 
 int /*<<< orphan*/  set_bit (int,void*) ; 
 scalar_t__ skb_network_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ncsi_rsp_handler_sma(struct ncsi_request *nr)
{
	struct ncsi_cmd_sma_pkt *cmd;
	struct ncsi_rsp_pkt *rsp;
	struct ncsi_dev_priv *ndp = nr->ndp;
	struct ncsi_channel *nc;
	struct ncsi_channel_mac_filter *ncf;
	unsigned long flags;
	void *bitmap;
	bool enabled;
	int index;


	/* Find the package and channel */
	rsp = (struct ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      NULL, &nc);
	if (!nc)
		return -ENODEV;

	/* According to NCSI spec 1.01, the mixed filter table
	 * isn't supported yet.
	 */
	cmd = (struct ncsi_cmd_sma_pkt *)skb_network_header(nr->cmd);
	enabled = cmd->at_e & 0x1;
	ncf = &nc->mac_filter;
	bitmap = &ncf->bitmap;

	if (cmd->index == 0 ||
	    cmd->index > ncf->n_uc + ncf->n_mc + ncf->n_mixed)
		return -ERANGE;

	index = (cmd->index - 1) * ETH_ALEN;
	spin_lock_irqsave(&nc->lock, flags);
	if (enabled) {
		set_bit(cmd->index - 1, bitmap);
		memcpy(&ncf->addrs[index], cmd->mac, ETH_ALEN);
	} else {
		clear_bit(cmd->index - 1, bitmap);
		memset(&ncf->addrs[index], 0, ETH_ALEN);
	}
	spin_unlock_irqrestore(&nc->lock, flags);

	return 0;
}