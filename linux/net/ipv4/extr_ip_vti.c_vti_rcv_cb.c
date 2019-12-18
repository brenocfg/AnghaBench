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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {scalar_t__ family; } ;
struct xfrm_mode {unsigned short family; } ;
struct xfrm_state {TYPE_3__ sel; struct xfrm_mode inner_mode; } ;
struct sk_buff {scalar_t__ len; struct net_device* dev; int /*<<< orphan*/  mark; } ;
struct pcpu_sw_netstats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_8__ {int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; } ;
struct net_device {int /*<<< orphan*/  tstats; TYPE_2__ stats; } ;
struct TYPE_10__ {int /*<<< orphan*/  i_key; } ;
struct ip_tunnel {int /*<<< orphan*/  net; TYPE_4__ parms; struct net_device* dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  protocol; } ;
struct TYPE_7__ {struct ip_tunnel* ip4; } ;
struct TYPE_11__ {TYPE_1__ tunnel; } ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMINSTATEMODEERROR ; 
 int /*<<< orphan*/  XFRM_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* XFRM_MODE_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  XFRM_POLICY_IN ; 
 TYPE_5__* XFRM_TUNNEL_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_scrub_packet (struct sk_buff*,int) ; 
 struct pcpu_sw_netstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 struct xfrm_state* xfrm_input_state (struct sk_buff*) ; 
 struct xfrm_mode* xfrm_ip2inner_mode (struct xfrm_state*,int /*<<< orphan*/ ) ; 
 int xfrm_policy_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,unsigned short) ; 

__attribute__((used)) static int vti_rcv_cb(struct sk_buff *skb, int err)
{
	unsigned short family;
	struct net_device *dev;
	struct pcpu_sw_netstats *tstats;
	struct xfrm_state *x;
	const struct xfrm_mode *inner_mode;
	struct ip_tunnel *tunnel = XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip4;
	u32 orig_mark = skb->mark;
	int ret;

	if (!tunnel)
		return 1;

	dev = tunnel->dev;

	if (err) {
		dev->stats.rx_errors++;
		dev->stats.rx_dropped++;

		return 0;
	}

	x = xfrm_input_state(skb);

	inner_mode = &x->inner_mode;

	if (x->sel.family == AF_UNSPEC) {
		inner_mode = xfrm_ip2inner_mode(x, XFRM_MODE_SKB_CB(skb)->protocol);
		if (inner_mode == NULL) {
			XFRM_INC_STATS(dev_net(skb->dev),
				       LINUX_MIB_XFRMINSTATEMODEERROR);
			return -EINVAL;
		}
	}

	family = inner_mode->family;

	skb->mark = be32_to_cpu(tunnel->parms.i_key);
	ret = xfrm_policy_check(NULL, XFRM_POLICY_IN, skb, family);
	skb->mark = orig_mark;

	if (!ret)
		return -EPERM;

	skb_scrub_packet(skb, !net_eq(tunnel->net, dev_net(skb->dev)));
	skb->dev = dev;

	tstats = this_cpu_ptr(dev->tstats);

	u64_stats_update_begin(&tstats->syncp);
	tstats->rx_packets++;
	tstats->rx_bytes += skb->len;
	u64_stats_update_end(&tstats->syncp);

	return 0;
}