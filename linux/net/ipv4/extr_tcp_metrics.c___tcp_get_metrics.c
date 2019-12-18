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
struct tcp_metrics_block {int /*<<< orphan*/  tcpm_daddr; int /*<<< orphan*/  tcpm_saddr; int /*<<< orphan*/  tcpm_next; } ;
struct net {int dummy; } ;
struct inetpeer_addr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 scalar_t__ addr_same (int /*<<< orphan*/ *,struct inetpeer_addr const*) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,struct net*) ; 
 struct tcp_metrics_block* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct tcp_metrics_block* tcp_get_encode (struct tcp_metrics_block*,int) ; 
 TYPE_1__* tcp_metrics_hash ; 
 int /*<<< orphan*/  tm_net (struct tcp_metrics_block*) ; 

__attribute__((used)) static struct tcp_metrics_block *__tcp_get_metrics(const struct inetpeer_addr *saddr,
						   const struct inetpeer_addr *daddr,
						   struct net *net, unsigned int hash)
{
	struct tcp_metrics_block *tm;
	int depth = 0;

	for (tm = rcu_dereference(tcp_metrics_hash[hash].chain); tm;
	     tm = rcu_dereference(tm->tcpm_next)) {
		if (addr_same(&tm->tcpm_saddr, saddr) &&
		    addr_same(&tm->tcpm_daddr, daddr) &&
		    net_eq(tm_net(tm), net))
			break;
		depth++;
	}
	return tcp_get_encode(tm, depth);
}