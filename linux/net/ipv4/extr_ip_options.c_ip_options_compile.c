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
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct ip_options {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_PARAMETERPROB ; 
 int __ip_options_compile (struct net*,struct ip_options*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ip_options_compile(struct net *net,
		       struct ip_options *opt, struct sk_buff *skb)
{
	int ret;
	__be32 info;

	ret = __ip_options_compile(net, opt, skb, &info);
	if (ret != 0 && skb)
		icmp_send(skb, ICMP_PARAMETERPROB, 0, info);
	return ret;
}