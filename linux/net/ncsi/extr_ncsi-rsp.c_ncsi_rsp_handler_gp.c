#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;
struct TYPE_5__ {TYPE_1__ common; } ;
struct ncsi_rsp_gp_pkt {int vlan_mode; int fc_mode; unsigned short mac_enable; int mac_cnt; int vlan_cnt; int /*<<< orphan*/  vlan_enable; int /*<<< orphan*/  aen_mode; int /*<<< orphan*/  link_mode; int /*<<< orphan*/  valid_modes; int /*<<< orphan*/  bc_mode; TYPE_2__ rsp; } ;
struct ncsi_request {int /*<<< orphan*/  rsp; struct ncsi_dev_priv* ndp; } ;
struct ncsi_dev_priv {int dummy; } ;
struct ncsi_channel_vlan_filter {void** vids; int /*<<< orphan*/  bitmap; } ;
struct ncsi_channel_mac_filter {int /*<<< orphan*/ * addrs; int /*<<< orphan*/  bitmap; } ;
struct ncsi_channel {int /*<<< orphan*/  lock; struct ncsi_channel_vlan_filter vlan_filter; struct ncsi_channel_mac_filter mac_filter; TYPE_3__* modes; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_6__ {int enable; int* data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ETH_ALEN ; 
 size_t NCSI_MODE_AEN ; 
 size_t NCSI_MODE_BC ; 
 size_t NCSI_MODE_ENABLE ; 
 size_t NCSI_MODE_FC ; 
 size_t NCSI_MODE_LINK ; 
 size_t NCSI_MODE_MC ; 
 size_t NCSI_MODE_TX_ENABLE ; 
 size_t NCSI_MODE_VLAN ; 
 int /*<<< orphan*/  clear_bit (int,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  ncsi_find_package_and_channel (struct ncsi_dev_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ncsi_channel**) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,void*) ; 
 scalar_t__ skb_network_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ncsi_rsp_handler_gp(struct ncsi_request *nr)
{
	struct ncsi_channel_vlan_filter *ncvf;
	struct ncsi_channel_mac_filter *ncmf;
	struct ncsi_dev_priv *ndp = nr->ndp;
	struct ncsi_rsp_gp_pkt *rsp;
	struct ncsi_channel *nc;
	unsigned short enable;
	unsigned char *pdata;
	unsigned long flags;
	void *bitmap;
	int i;

	/* Find the channel */
	rsp = (struct ncsi_rsp_gp_pkt *)skb_network_header(nr->rsp);
	ncsi_find_package_and_channel(ndp, rsp->rsp.common.channel,
				      NULL, &nc);
	if (!nc)
		return -ENODEV;

	/* Modes with explicit enabled indications */
	if (ntohl(rsp->valid_modes) & 0x1) {	/* BC filter mode */
		nc->modes[NCSI_MODE_BC].enable = 1;
		nc->modes[NCSI_MODE_BC].data[0] = ntohl(rsp->bc_mode);
	}
	if (ntohl(rsp->valid_modes) & 0x2)	/* Channel enabled */
		nc->modes[NCSI_MODE_ENABLE].enable = 1;
	if (ntohl(rsp->valid_modes) & 0x4)	/* Channel Tx enabled */
		nc->modes[NCSI_MODE_TX_ENABLE].enable = 1;
	if (ntohl(rsp->valid_modes) & 0x8)	/* MC filter mode */
		nc->modes[NCSI_MODE_MC].enable = 1;

	/* Modes without explicit enabled indications */
	nc->modes[NCSI_MODE_LINK].enable = 1;
	nc->modes[NCSI_MODE_LINK].data[0] = ntohl(rsp->link_mode);
	nc->modes[NCSI_MODE_VLAN].enable = 1;
	nc->modes[NCSI_MODE_VLAN].data[0] = rsp->vlan_mode;
	nc->modes[NCSI_MODE_FC].enable = 1;
	nc->modes[NCSI_MODE_FC].data[0] = rsp->fc_mode;
	nc->modes[NCSI_MODE_AEN].enable = 1;
	nc->modes[NCSI_MODE_AEN].data[0] = ntohl(rsp->aen_mode);

	/* MAC addresses filter table */
	pdata = (unsigned char *)rsp + 48;
	enable = rsp->mac_enable;
	ncmf = &nc->mac_filter;
	spin_lock_irqsave(&nc->lock, flags);
	bitmap = &ncmf->bitmap;
	for (i = 0; i < rsp->mac_cnt; i++, pdata += 6) {
		if (!(enable & (0x1 << i)))
			clear_bit(i, bitmap);
		else
			set_bit(i, bitmap);

		memcpy(&ncmf->addrs[i * ETH_ALEN], pdata, ETH_ALEN);
	}
	spin_unlock_irqrestore(&nc->lock, flags);

	/* VLAN filter table */
	enable = ntohs(rsp->vlan_enable);
	ncvf = &nc->vlan_filter;
	bitmap = &ncvf->bitmap;
	spin_lock_irqsave(&nc->lock, flags);
	for (i = 0; i < rsp->vlan_cnt; i++, pdata += 2) {
		if (!(enable & (0x1 << i)))
			clear_bit(i, bitmap);
		else
			set_bit(i, bitmap);

		ncvf->vids[i] = ntohs(*(__be16 *)pdata);
	}
	spin_unlock_irqrestore(&nc->lock, flags);

	return 0;
}