#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tag ;
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {char* data; int /*<<< orphan*/  protocol; int /*<<< orphan*/  truesize; struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct mpoa_client {TYPE_2__* eg_ops; } ;
struct llc_snap_hdr {int dummy; } ;
struct atm_vcc {scalar_t__ proto_data; } ;
struct atm_skb_data {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  DH_length; int /*<<< orphan*/  DLL_header; } ;
struct TYPE_10__ {int /*<<< orphan*/  packets_rcvd; int /*<<< orphan*/  latest_ip_addr; TYPE_1__ ctrl_info; struct atm_vcc* shortcut; } ;
typedef  TYPE_3__ eg_cache_entry ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_11__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* put ) (TYPE_3__*) ;TYPE_3__* (* get_by_tag ) (int /*<<< orphan*/ ,struct mpoa_client*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_SKB (struct sk_buff*) ; 
 int /*<<< orphan*/  atm_return (struct atm_vcc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct mpoa_client* find_mpc_by_lec (struct net_device*) ; 
 TYPE_7__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  llc_snap_mpoa_ctrl ; 
 int /*<<< orphan*/  llc_snap_mpoa_data ; 
 int /*<<< orphan*/  llc_snap_mpoa_data_tagged ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpc_vcc_close (struct atm_vcc*,struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  purge_egress_shortcut (struct atm_vcc*,int /*<<< orphan*/ *) ; 
 struct sock* sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 TYPE_3__* stub2 (int /*<<< orphan*/ ,struct mpoa_client*) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*) ; 

__attribute__((used)) static void mpc_push(struct atm_vcc *vcc, struct sk_buff *skb)
{
	struct net_device *dev = (struct net_device *)vcc->proto_data;
	struct sk_buff *new_skb;
	eg_cache_entry *eg;
	struct mpoa_client *mpc;
	__be32 tag;
	char *tmp;

	ddprintk("(%s)\n", dev->name);
	if (skb == NULL) {
		dprintk("(%s) null skb, closing VCC\n", dev->name);
		mpc_vcc_close(vcc, dev);
		return;
	}

	skb->dev = dev;
	if (memcmp(skb->data, &llc_snap_mpoa_ctrl,
		   sizeof(struct llc_snap_hdr)) == 0) {
		struct sock *sk = sk_atm(vcc);

		dprintk("(%s) control packet arrived\n", dev->name);
		/* Pass control packets to daemon */
		skb_queue_tail(&sk->sk_receive_queue, skb);
		sk->sk_data_ready(sk);
		return;
	}

	/* data coming over the shortcut */
	atm_return(vcc, skb->truesize);

	mpc = find_mpc_by_lec(dev);
	if (mpc == NULL) {
		pr_info("(%s) unknown MPC\n", dev->name);
		return;
	}

	if (memcmp(skb->data, &llc_snap_mpoa_data_tagged,
		   sizeof(struct llc_snap_hdr)) == 0) { /* MPOA tagged data */
		ddprintk("(%s) tagged data packet arrived\n", dev->name);

	} else if (memcmp(skb->data, &llc_snap_mpoa_data,
			  sizeof(struct llc_snap_hdr)) == 0) { /* MPOA data */
		pr_info("(%s) Unsupported non-tagged data packet arrived.  Purging\n",
			dev->name);
		dev_kfree_skb_any(skb);
		return;
	} else {
		pr_info("(%s) garbage arrived, purging\n", dev->name);
		dev_kfree_skb_any(skb);
		return;
	}

	tmp = skb->data + sizeof(struct llc_snap_hdr);
	tag = *(__be32 *)tmp;

	eg = mpc->eg_ops->get_by_tag(tag, mpc);
	if (eg == NULL) {
		pr_info("mpoa: (%s) Didn't find egress cache entry, tag = %u\n",
			dev->name, tag);
		purge_egress_shortcut(vcc, NULL);
		dev_kfree_skb_any(skb);
		return;
	}

	/*
	 * See if ingress MPC is using shortcut we opened as a return channel.
	 * This means we have a bi-directional vcc opened by us.
	 */
	if (eg->shortcut == NULL) {
		eg->shortcut = vcc;
		pr_info("(%s) egress SVC in use\n", dev->name);
	}

	skb_pull(skb, sizeof(struct llc_snap_hdr) + sizeof(tag));
					/* get rid of LLC/SNAP header */
	new_skb = skb_realloc_headroom(skb, eg->ctrl_info.DH_length);
					/* LLC/SNAP is shorter than MAC header :( */
	dev_kfree_skb_any(skb);
	if (new_skb == NULL) {
		mpc->eg_ops->put(eg);
		return;
	}
	skb_push(new_skb, eg->ctrl_info.DH_length);     /* add MAC header */
	skb_copy_to_linear_data(new_skb, eg->ctrl_info.DLL_header,
				eg->ctrl_info.DH_length);
	new_skb->protocol = eth_type_trans(new_skb, dev);
	skb_reset_network_header(new_skb);

	eg->latest_ip_addr = ip_hdr(new_skb)->saddr;
	eg->packets_rcvd++;
	mpc->eg_ops->put(eg);

	memset(ATM_SKB(new_skb), 0, sizeof(struct atm_skb_data));
	netif_rx(new_skb);
}