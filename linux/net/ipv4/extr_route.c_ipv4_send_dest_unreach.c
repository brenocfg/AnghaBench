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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct iphdr {int dummy; } ;
struct ip_options {int optlen; } ;
typedef  int /*<<< orphan*/  opt ;
struct TYPE_2__ {int version; int ihl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_HOST_UNREACH ; 
 int /*<<< orphan*/  __icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ip_options*) ; 
 int __ip_options_compile (int /*<<< orphan*/ ,struct ip_options*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct ip_options*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pskb_network_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void ipv4_send_dest_unreach(struct sk_buff *skb)
{
	struct ip_options opt;
	int res;

	/* Recompile ip options since IPCB may not be valid anymore.
	 * Also check we have a reasonable ipv4 header.
	 */
	if (!pskb_network_may_pull(skb, sizeof(struct iphdr)) ||
	    ip_hdr(skb)->version != 4 || ip_hdr(skb)->ihl < 5)
		return;

	memset(&opt, 0, sizeof(opt));
	if (ip_hdr(skb)->ihl > 5) {
		if (!pskb_network_may_pull(skb, ip_hdr(skb)->ihl * 4))
			return;
		opt.optlen = ip_hdr(skb)->ihl * 4 - sizeof(struct iphdr);

		rcu_read_lock();
		res = __ip_options_compile(dev_net(skb->dev), &opt, skb, NULL);
		rcu_read_unlock();

		if (res)
			return;
	}
	__icmp_send(skb, ICMP_DEST_UNREACH, ICMP_HOST_UNREACH, 0, &opt);
}