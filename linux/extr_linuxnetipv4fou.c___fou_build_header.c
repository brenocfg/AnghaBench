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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct ip_tunnel_encap {scalar_t__ sport; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int iptunnel_handle_offloads (struct sk_buff*,int) ; 
 int /*<<< orphan*/  udp_flow_src_port (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int __fou_build_header(struct sk_buff *skb, struct ip_tunnel_encap *e,
		       u8 *protocol, __be16 *sport, int type)
{
	int err;

	err = iptunnel_handle_offloads(skb, type);
	if (err)
		return err;

	*sport = e->sport ? : udp_flow_src_port(dev_net(skb->dev),
						skb, 0, 0, false);

	return 0;
}