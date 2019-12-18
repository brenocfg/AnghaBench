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
typedef  struct tcp_congestion_ops {int flags; int /*<<< orphan*/  owner; } const tcp_congestion_ops ;
struct sock {int dummy; } ;
struct inet_connection_sock {int icsk_ca_setsockopt; struct tcp_congestion_ops const* icsk_ca_ops; scalar_t__ icsk_ca_dst_locked; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int EPERM ; 
 int TCP_CONG_NON_RESTRICTED ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 struct tcp_congestion_ops const* tcp_ca_find (char const*) ; 
 struct tcp_congestion_ops const* tcp_ca_find_autoload (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  tcp_reinit_congestion_control (struct sock*,struct tcp_congestion_ops const*) ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 

int tcp_set_congestion_control(struct sock *sk, const char *name, bool load,
			       bool reinit, bool cap_net_admin)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	const struct tcp_congestion_ops *ca;
	int err = 0;

	if (icsk->icsk_ca_dst_locked)
		return -EPERM;

	rcu_read_lock();
	if (!load)
		ca = tcp_ca_find(name);
	else
		ca = tcp_ca_find_autoload(sock_net(sk), name);

	/* No change asking for existing value */
	if (ca == icsk->icsk_ca_ops) {
		icsk->icsk_ca_setsockopt = 1;
		goto out;
	}

	if (!ca) {
		err = -ENOENT;
	} else if (!load) {
		const struct tcp_congestion_ops *old_ca = icsk->icsk_ca_ops;

		if (try_module_get(ca->owner)) {
			if (reinit) {
				tcp_reinit_congestion_control(sk, ca);
			} else {
				icsk->icsk_ca_ops = ca;
				module_put(old_ca->owner);
			}
		} else {
			err = -EBUSY;
		}
	} else if (!((ca->flags & TCP_CONG_NON_RESTRICTED) || cap_net_admin)) {
		err = -EPERM;
	} else if (!try_module_get(ca->owner)) {
		err = -EBUSY;
	} else {
		tcp_reinit_congestion_control(sk, ca);
	}
 out:
	rcu_read_unlock();
	return err;
}