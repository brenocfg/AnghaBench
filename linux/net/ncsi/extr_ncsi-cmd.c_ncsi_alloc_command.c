#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct net_device {int needed_tailroom; } ;
struct ncsi_request {struct sk_buff* cmd; } ;
struct ncsi_dev {struct net_device* dev; } ;
struct ncsi_dev_priv {struct ncsi_dev ndev; } ;
struct ncsi_cmd_pkt_hdr {int dummy; } ;
struct ncsi_cmd_arg {int payload; int /*<<< orphan*/  req_flags; struct ncsi_dev_priv* ndp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_NCSI ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int LL_RESERVED_SPACE (struct net_device*) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct ncsi_request* ncsi_alloc_request (struct ncsi_dev_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncsi_free_request (struct ncsi_request*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

__attribute__((used)) static struct ncsi_request *ncsi_alloc_command(struct ncsi_cmd_arg *nca)
{
	struct ncsi_dev_priv *ndp = nca->ndp;
	struct ncsi_dev *nd = &ndp->ndev;
	struct net_device *dev = nd->dev;
	int hlen = LL_RESERVED_SPACE(dev);
	int tlen = dev->needed_tailroom;
	int len = hlen + tlen;
	struct sk_buff *skb;
	struct ncsi_request *nr;

	nr = ncsi_alloc_request(ndp, nca->req_flags);
	if (!nr)
		return NULL;

	/* NCSI command packet has 16-bytes header, payload, 4 bytes checksum.
	 * The packet needs padding if its payload is less than 26 bytes to
	 * meet 64 bytes minimal ethernet frame length.
	 */
	len += sizeof(struct ncsi_cmd_pkt_hdr) + 4;
	if (nca->payload < 26)
		len += 26;
	else
		len += nca->payload;

	/* Allocate skb */
	skb = alloc_skb(len, GFP_ATOMIC);
	if (!skb) {
		ncsi_free_request(nr);
		return NULL;
	}

	nr->cmd = skb;
	skb_reserve(skb, hlen);
	skb_reset_network_header(skb);

	skb->dev = dev;
	skb->protocol = htons(ETH_P_NCSI);

	return nr;
}