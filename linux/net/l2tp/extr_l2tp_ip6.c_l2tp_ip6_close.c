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
struct sock {int /*<<< orphan*/  sk_bind_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2tp_ip6_lock ; 
 int /*<<< orphan*/  sk_common_release (struct sock*) ; 
 int /*<<< orphan*/  sk_del_node_init (struct sock*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2tp_ip6_close(struct sock *sk, long timeout)
{
	write_lock_bh(&l2tp_ip6_lock);
	hlist_del_init(&sk->sk_bind_node);
	sk_del_node_init(sk);
	write_unlock_bh(&l2tp_ip6_lock);

	sk_common_release(sk);
}