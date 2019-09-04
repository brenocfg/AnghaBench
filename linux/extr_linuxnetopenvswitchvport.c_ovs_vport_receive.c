#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vport {int /*<<< orphan*/  dp; } ;
struct sw_flow_key {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  mark; int /*<<< orphan*/  dev; } ;
struct ip_tunnel_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ cutlen; scalar_t__ mru; struct vport* input_vport; } ;

/* Variables and functions */
 TYPE_1__* OVS_CB (struct sk_buff*) ; 
 scalar_t__ dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ ovs_dp_get_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_dp_process_packet (struct sk_buff*,struct sw_flow_key*) ; 
 int ovs_flow_key_extract (struct ip_tunnel_info const*,struct sk_buff*,struct sw_flow_key*) ; 
 int /*<<< orphan*/  skb_scrub_packet (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

int ovs_vport_receive(struct vport *vport, struct sk_buff *skb,
		      const struct ip_tunnel_info *tun_info)
{
	struct sw_flow_key key;
	int error;

	OVS_CB(skb)->input_vport = vport;
	OVS_CB(skb)->mru = 0;
	OVS_CB(skb)->cutlen = 0;
	if (unlikely(dev_net(skb->dev) != ovs_dp_get_net(vport->dp))) {
		u32 mark;

		mark = skb->mark;
		skb_scrub_packet(skb, true);
		skb->mark = mark;
		tun_info = NULL;
	}

	/* Extract flow from 'skb' into 'key'. */
	error = ovs_flow_key_extract(tun_info, skb, &key);
	if (unlikely(error)) {
		kfree_skb(skb);
		return error;
	}
	ovs_dp_process_packet(skb, &key);
	return 0;
}