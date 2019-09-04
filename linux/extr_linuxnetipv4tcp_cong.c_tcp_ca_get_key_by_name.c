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
typedef  int /*<<< orphan*/  u32 ;
struct tcp_congestion_ops {int flags; int /*<<< orphan*/  key; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_CA_UNSPEC ; 
 int TCP_CONG_NEEDS_ECN ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct tcp_congestion_ops* tcp_ca_find_autoload (struct net*,char const*) ; 

u32 tcp_ca_get_key_by_name(struct net *net, const char *name, bool *ecn_ca)
{
	const struct tcp_congestion_ops *ca;
	u32 key = TCP_CA_UNSPEC;

	might_sleep();

	rcu_read_lock();
	ca = tcp_ca_find_autoload(net, name);
	if (ca) {
		key = ca->key;
		*ecn_ca = ca->flags & TCP_CONG_NEEDS_ECN;
	}
	rcu_read_unlock();

	return key;
}