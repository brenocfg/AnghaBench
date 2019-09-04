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
struct tcp_congestion_ops {int /*<<< orphan*/  flags; int /*<<< orphan*/  owner; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcp_congestion_control; } ;
struct net {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  TCP_CONG_NON_RESTRICTED ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct tcp_congestion_ops* tcp_ca_find_autoload (struct net*,char const*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 struct tcp_congestion_ops* xchg (int /*<<< orphan*/ *,struct tcp_congestion_ops*) ; 

int tcp_set_default_congestion_control(struct net *net, const char *name)
{
	struct tcp_congestion_ops *ca;
	const struct tcp_congestion_ops *prev;
	int ret;

	rcu_read_lock();
	ca = tcp_ca_find_autoload(net, name);
	if (!ca) {
		ret = -ENOENT;
	} else if (!try_module_get(ca->owner)) {
		ret = -EBUSY;
	} else {
		prev = xchg(&net->ipv4.tcp_congestion_control, ca);
		if (prev)
			module_put(prev->owner);

		ca->flags |= TCP_CONG_NON_RESTRICTED;
		ret = 0;
	}
	rcu_read_unlock();

	return ret;
}