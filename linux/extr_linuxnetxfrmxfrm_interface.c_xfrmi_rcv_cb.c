#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ family; } ;
struct xfrm_state {TYPE_2__ sel; struct xfrm_mode* inner_mode; } ;
struct xfrm_mode {TYPE_3__* afinfo; } ;
struct xfrm_if {int /*<<< orphan*/  net; struct net_device* dev; } ;
struct sk_buff {scalar_t__ len; struct net_device* dev; int /*<<< orphan*/  sp; } ;
struct pcpu_sw_netstats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; } ;
struct net_device {int /*<<< orphan*/  tstats; TYPE_1__ stats; } ;
struct TYPE_8__ {int /*<<< orphan*/  protocol; } ;
struct TYPE_7__ {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMINSTATEMODEERROR ; 
 int /*<<< orphan*/  XFRM_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* XFRM_MODE_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  XFRM_POLICY_IN ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pcpu_sw_netstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 struct xfrm_state* xfrm_input_state (struct sk_buff*) ; 
 struct xfrm_mode* xfrm_ip2inner_mode (struct xfrm_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_policy_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct xfrm_if* xfrmi_lookup (int /*<<< orphan*/ ,struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrmi_scrub_packet (struct sk_buff*,int) ; 
 int /*<<< orphan*/  xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int xfrmi_rcv_cb(struct sk_buff *skb, int err)
{
	struct pcpu_sw_netstats *tstats;
	struct xfrm_mode *inner_mode;
	struct net_device *dev;
	struct xfrm_state *x;
	struct xfrm_if *xi;
	bool xnet;

	if (err && !skb->sp)
		return 0;

	x = xfrm_input_state(skb);

	xi = xfrmi_lookup(xs_net(x), x);
	if (!xi)
		return 1;

	dev = xi->dev;
	skb->dev = dev;

	if (err) {
		dev->stats.rx_errors++;
		dev->stats.rx_dropped++;

		return 0;
	}

	xnet = !net_eq(xi->net, dev_net(skb->dev));

	if (xnet) {
		inner_mode = x->inner_mode;

		if (x->sel.family == AF_UNSPEC) {
			inner_mode = xfrm_ip2inner_mode(x, XFRM_MODE_SKB_CB(skb)->protocol);
			if (inner_mode == NULL) {
				XFRM_INC_STATS(dev_net(skb->dev),
					       LINUX_MIB_XFRMINSTATEMODEERROR);
				return -EINVAL;
			}
		}

		if (!xfrm_policy_check(NULL, XFRM_POLICY_IN, skb,
				       inner_mode->afinfo->family))
			return -EPERM;
	}

	xfrmi_scrub_packet(skb, xnet);

	tstats = this_cpu_ptr(dev->tstats);

	u64_stats_update_begin(&tstats->syncp);
	tstats->rx_packets++;
	tstats->rx_bytes += skb->len;
	u64_stats_update_end(&tstats->syncp);

	return 0;
}