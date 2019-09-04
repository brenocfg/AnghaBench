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
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct netns_ipvs {int sync_state; int /*<<< orphan*/  sync_mutex; int /*<<< orphan*/  bcfg; int /*<<< orphan*/  mcfg; } ;
struct netlink_callback {int* args; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int IP_VS_STATE_BACKUP ; 
 int IP_VS_STATE_MASTER ; 
 scalar_t__ ip_vs_genl_dump_daemon (struct sk_buff*,int,int /*<<< orphan*/ *,struct netlink_callback*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct netns_ipvs* net_ipvs (struct net*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_vs_genl_dump_daemons(struct sk_buff *skb,
				   struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	struct netns_ipvs *ipvs = net_ipvs(net);

	mutex_lock(&ipvs->sync_mutex);
	if ((ipvs->sync_state & IP_VS_STATE_MASTER) && !cb->args[0]) {
		if (ip_vs_genl_dump_daemon(skb, IP_VS_STATE_MASTER,
					   &ipvs->mcfg, cb) < 0)
			goto nla_put_failure;

		cb->args[0] = 1;
	}

	if ((ipvs->sync_state & IP_VS_STATE_BACKUP) && !cb->args[1]) {
		if (ip_vs_genl_dump_daemon(skb, IP_VS_STATE_BACKUP,
					   &ipvs->bcfg, cb) < 0)
			goto nla_put_failure;

		cb->args[1] = 1;
	}

nla_put_failure:
	mutex_unlock(&ipvs->sync_mutex);

	return skb->len;
}