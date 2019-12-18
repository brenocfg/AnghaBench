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
typedef  int u32 ;
struct xdp_buff {void* data; void* data_meta; void* data_end; int /*<<< orphan*/ * rxq; scalar_t__ data_hard_start; } ;
struct sk_buff {int tail; int data_len; int end; int data; int mac_header; int len; int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; } ;
struct netdev_rx_queue {int /*<<< orphan*/  xdp_rxq; } ;
struct ethhdr {scalar_t__ h_proto; int /*<<< orphan*/  h_dest; } ;
struct bpf_prog {int dummy; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int /*<<< orphan*/ ) ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NET_SKB_PAD ; 
#define  XDP_ABORTED 132 
#define  XDP_DROP 131 
 scalar_t__ XDP_PACKET_HEADROOM ; 
#define  XDP_PASS 130 
#define  XDP_REDIRECT 129 
#define  XDP_TX 128 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int) ; 
 int bpf_prog_run_xdp (struct bpf_prog*,struct xdp_buff*) ; 
 int /*<<< orphan*/  bpf_warn_invalid_xdp_action (int) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int is_multicast_ether_addr_64bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct netdev_rx_queue* netif_get_rxqueue (struct sk_buff*) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 int skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 scalar_t__ skb_is_nonlinear (struct sk_buff*) ; 
 scalar_t__ skb_is_tc_redirected (struct sk_buff*) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 int skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_metadata_set (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,int) ; 
 int /*<<< orphan*/  trace_xdp_exception (int /*<<< orphan*/ ,struct bpf_prog*,int) ; 

__attribute__((used)) static u32 netif_receive_generic_xdp(struct sk_buff *skb,
				     struct xdp_buff *xdp,
				     struct bpf_prog *xdp_prog)
{
	struct netdev_rx_queue *rxqueue;
	void *orig_data, *orig_data_end;
	u32 metalen, act = XDP_DROP;
	__be16 orig_eth_type;
	struct ethhdr *eth;
	bool orig_bcast;
	int hlen, off;
	u32 mac_len;

	/* Reinjected packets coming from act_mirred or similar should
	 * not get XDP generic processing.
	 */
	if (skb_cloned(skb) || skb_is_tc_redirected(skb))
		return XDP_PASS;

	/* XDP packets must be linear and must have sufficient headroom
	 * of XDP_PACKET_HEADROOM bytes. This is the guarantee that also
	 * native XDP provides, thus we need to do it here as well.
	 */
	if (skb_is_nonlinear(skb) ||
	    skb_headroom(skb) < XDP_PACKET_HEADROOM) {
		int hroom = XDP_PACKET_HEADROOM - skb_headroom(skb);
		int troom = skb->tail + skb->data_len - skb->end;

		/* In case we have to go down the path and also linearize,
		 * then lets do the pskb_expand_head() work just once here.
		 */
		if (pskb_expand_head(skb,
				     hroom > 0 ? ALIGN(hroom, NET_SKB_PAD) : 0,
				     troom > 0 ? troom + 128 : 0, GFP_ATOMIC))
			goto do_drop;
		if (skb_linearize(skb))
			goto do_drop;
	}

	/* The XDP program wants to see the packet starting at the MAC
	 * header.
	 */
	mac_len = skb->data - skb_mac_header(skb);
	hlen = skb_headlen(skb) + mac_len;
	xdp->data = skb->data - mac_len;
	xdp->data_meta = xdp->data;
	xdp->data_end = xdp->data + hlen;
	xdp->data_hard_start = skb->data - skb_headroom(skb);
	orig_data_end = xdp->data_end;
	orig_data = xdp->data;
	eth = (struct ethhdr *)xdp->data;
	orig_bcast = is_multicast_ether_addr_64bits(eth->h_dest);
	orig_eth_type = eth->h_proto;

	rxqueue = netif_get_rxqueue(skb);
	xdp->rxq = &rxqueue->xdp_rxq;

	act = bpf_prog_run_xdp(xdp_prog, xdp);

	/* check if bpf_xdp_adjust_head was used */
	off = xdp->data - orig_data;
	if (off) {
		if (off > 0)
			__skb_pull(skb, off);
		else if (off < 0)
			__skb_push(skb, -off);

		skb->mac_header += off;
		skb_reset_network_header(skb);
	}

	/* check if bpf_xdp_adjust_tail was used. it can only "shrink"
	 * pckt.
	 */
	off = orig_data_end - xdp->data_end;
	if (off != 0) {
		skb_set_tail_pointer(skb, xdp->data_end - xdp->data);
		skb->len -= off;

	}

	/* check if XDP changed eth hdr such SKB needs update */
	eth = (struct ethhdr *)xdp->data;
	if ((orig_eth_type != eth->h_proto) ||
	    (orig_bcast != is_multicast_ether_addr_64bits(eth->h_dest))) {
		__skb_push(skb, ETH_HLEN);
		skb->protocol = eth_type_trans(skb, skb->dev);
	}

	switch (act) {
	case XDP_REDIRECT:
	case XDP_TX:
		__skb_push(skb, mac_len);
		break;
	case XDP_PASS:
		metalen = xdp->data - xdp->data_meta;
		if (metalen)
			skb_metadata_set(skb, metalen);
		break;
	default:
		bpf_warn_invalid_xdp_action(act);
		/* fall through */
	case XDP_ABORTED:
		trace_xdp_exception(skb->dev, xdp_prog, act);
		/* fall through */
	case XDP_DROP:
	do_drop:
		kfree_skb(skb);
		break;
	}

	return act;
}