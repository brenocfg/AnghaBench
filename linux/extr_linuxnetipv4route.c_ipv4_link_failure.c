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
struct rtable {int /*<<< orphan*/  dst; } ;
struct iphdr {int dummy; } ;
struct ip_options {int optlen; } ;
typedef  int /*<<< orphan*/  opt ;
struct TYPE_2__ {int ihl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_HOST_UNREACH ; 
 int /*<<< orphan*/  __icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ip_options*) ; 
 int __ip_options_compile (int /*<<< orphan*/ ,struct ip_options*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_set_expires (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct ip_options*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct rtable* skb_rtable (struct sk_buff*) ; 

__attribute__((used)) static void ipv4_link_failure(struct sk_buff *skb)
{
	struct ip_options opt;
	struct rtable *rt;
	int res;

	/* Recompile ip options since IPCB may not be valid anymore.
	 */
	memset(&opt, 0, sizeof(opt));
	opt.optlen = ip_hdr(skb)->ihl*4 - sizeof(struct iphdr);

	rcu_read_lock();
	res = __ip_options_compile(dev_net(skb->dev), &opt, skb, NULL);
	rcu_read_unlock();

	if (res)
		return;

	__icmp_send(skb, ICMP_DEST_UNREACH, ICMP_HOST_UNREACH, 0, &opt);

	rt = skb_rtable(skb);
	if (rt)
		dst_set_expires(&rt->dst, 0);
}