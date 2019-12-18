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
struct sock {int /*<<< orphan*/  sk_dst_cache; } ;
struct dst_entry {TYPE_1__* dev; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int NETIF_F_LOOPBACK ; 
 struct dst_entry* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static inline int sock_is_loopback(struct sock *sk)
{
	struct dst_entry *dst;
	int loopback = 0;
	rcu_read_lock();
	dst = rcu_dereference(sk->sk_dst_cache);
	if (dst && dst->dev &&
	    (dst->dev->features & NETIF_F_LOOPBACK))
		loopback = 1;
	rcu_read_unlock();
	return loopback;
}