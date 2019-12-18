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
struct tnl_ptk_info {scalar_t__ proto; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct net {int dummy; } ;
struct ip_tunnel_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_TEB ; 
 int PACKET_NEXT ; 
 int __ipgre_rcv (struct sk_buff*,struct tnl_ptk_info const*,struct ip_tunnel_net*,int,int) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gre_tap_net_id ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipgre_net_id ; 
 struct ip_tunnel_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipgre_rcv(struct sk_buff *skb, const struct tnl_ptk_info *tpi,
		     int hdr_len)
{
	struct net *net = dev_net(skb->dev);
	struct ip_tunnel_net *itn;
	int res;

	if (tpi->proto == htons(ETH_P_TEB))
		itn = net_generic(net, gre_tap_net_id);
	else
		itn = net_generic(net, ipgre_net_id);

	res = __ipgre_rcv(skb, tpi, itn, hdr_len, false);
	if (res == PACKET_NEXT && tpi->proto == htons(ETH_P_TEB)) {
		/* ipgre tunnels in collect metadata mode should receive
		 * also ETH_P_TEB traffic.
		 */
		itn = net_generic(net, ipgre_net_id);
		res = __ipgre_rcv(skb, tpi, itn, hdr_len, true);
	}
	return res;
}