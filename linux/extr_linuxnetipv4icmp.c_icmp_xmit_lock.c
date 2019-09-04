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
struct TYPE_2__ {int /*<<< orphan*/  slock; } ;
struct sock {TYPE_1__ sk_lock; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct sock* icmp_sk (struct net*) ; 
 int /*<<< orphan*/  spin_trylock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct sock *icmp_xmit_lock(struct net *net)
{
	struct sock *sk;

	sk = icmp_sk(net);

	if (unlikely(!spin_trylock(&sk->sk_lock.slock))) {
		/* This can happen if the output path signals a
		 * dst_link_failure() for an outgoing ICMP packet.
		 */
		return NULL;
	}
	return sk;
}