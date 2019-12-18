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
struct ncsi_cmd_svf_pkt {int index; int enable; int /*<<< orphan*/  vlan; } ;
struct ncsi_channel_vlan_filter {int n_vids; scalar_t__* vids; int /*<<< orphan*/  bitmap; } ;
struct ncsi_channel {int /*<<< orphan*/  lock; struct ncsi_channel_vlan_filter vlan_filter; } ;

/* Variables and functions */
 int ENODEV ; 
 int ERANGE ; 
 int /*<<< orphan*/  ncsi_find_package_and_channel (struct ncsi_dev_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ncsi_channel**) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,void*) ; 
 scalar_t__ skb_network_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int,void*) ; 

__attribute__((used)) static int ncsi_rsp_handler_svf(struct ncsi_request *nr)
{
	struct ncsi_cmd_svf_pkt *cmd;
	struct ncsi_rsp_pkt *rsp;
	struct ncsi_dev_priv *ndp = nr->ndp;
	struct ncsi_channel *nc;
	struct ncsi_channel_vlan_filter *ncf;
	unsigned long flags;
	void *bitmap;

	/* Find the package and channel */
	rsp = (struct ncsi_rsp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      NULL, &nc);
	if (!nc)
		return -ENODEV;

	cmd = (struct ncsi_cmd_svf_pkt *)skb_network_header(nr->cmd);
	ncf = &nc->vlan_filter;
	if (cmd->index == 0 || cmd->index > ncf->n_vids)
		return -ERANGE;

	/* Add or remove the VLAN filter. Remember HW indexes from 1 */
	spin_lock_irqsave(&nc->lock, flags);
	bitmap = &ncf->bitmap;
	if (!(cmd->enable & 0x1)) {
		if (test_and_clear_bit(cmd->index - 1, bitmap))
			ncf->vids[cmd->index - 1] = 0;
	} else {
		set_bit(cmd->index - 1, bitmap);
		ncf->vids[cmd->index - 1] = ntohs(cmd->vlan);
	}
	spin_unlock_irqrestore(&nc->lock, flags);

	return 0;
}