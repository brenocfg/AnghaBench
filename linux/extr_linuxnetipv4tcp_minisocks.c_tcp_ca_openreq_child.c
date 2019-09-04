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
typedef  scalar_t__ u32 ;
struct tcp_congestion_ops {int /*<<< orphan*/  owner; } ;
struct sock {int dummy; } ;
struct inet_connection_sock {struct tcp_congestion_ops const* icsk_ca_ops; int /*<<< orphan*/  icsk_ca_setsockopt; int /*<<< orphan*/  icsk_ca_dst_locked; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTAX_CC_ALGO ; 
 int /*<<< orphan*/  TCP_CA_Open ; 
 scalar_t__ TCP_CA_UNSPEC ; 
 scalar_t__ dst_metric (struct dst_entry const*,int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  tcp_assign_congestion_control (struct sock*) ; 
 int /*<<< orphan*/  tcp_ca_dst_locked (struct dst_entry const*) ; 
 struct tcp_congestion_ops* tcp_ca_find_key (scalar_t__) ; 
 int /*<<< orphan*/  tcp_set_ca_state (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 

void tcp_ca_openreq_child(struct sock *sk, const struct dst_entry *dst)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	u32 ca_key = dst_metric(dst, RTAX_CC_ALGO);
	bool ca_got_dst = false;

	if (ca_key != TCP_CA_UNSPEC) {
		const struct tcp_congestion_ops *ca;

		rcu_read_lock();
		ca = tcp_ca_find_key(ca_key);
		if (likely(ca && try_module_get(ca->owner))) {
			icsk->icsk_ca_dst_locked = tcp_ca_dst_locked(dst);
			icsk->icsk_ca_ops = ca;
			ca_got_dst = true;
		}
		rcu_read_unlock();
	}

	/* If no valid choice made yet, assign current system default ca. */
	if (!ca_got_dst &&
	    (!icsk->icsk_ca_setsockopt ||
	     !try_module_get(icsk->icsk_ca_ops->owner)))
		tcp_assign_congestion_control(sk);

	tcp_set_ca_state(sk, TCP_CA_Open);
}