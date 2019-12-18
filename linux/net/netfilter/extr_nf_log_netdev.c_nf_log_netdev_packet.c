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
typedef  int /*<<< orphan*/  u_int8_t ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct nf_loginfo {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_log_l2packet (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct sk_buff const*,struct net_device const*,struct net_device const*,struct nf_loginfo const*,char const*) ; 

__attribute__((used)) static void nf_log_netdev_packet(struct net *net, u_int8_t pf,
				 unsigned int hooknum,
				 const struct sk_buff *skb,
				 const struct net_device *in,
				 const struct net_device *out,
				 const struct nf_loginfo *loginfo,
				 const char *prefix)
{
	nf_log_l2packet(net, pf, skb->protocol, hooknum, skb, in, out,
			loginfo, prefix);
}