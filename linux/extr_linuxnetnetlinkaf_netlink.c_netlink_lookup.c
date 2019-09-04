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
struct sock {int dummy; } ;
struct netlink_table {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct sock* __netlink_lookup (struct netlink_table*,int /*<<< orphan*/ ,struct net*) ; 
 struct netlink_table* nl_table ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 

__attribute__((used)) static struct sock *netlink_lookup(struct net *net, int protocol, u32 portid)
{
	struct netlink_table *table = &nl_table[protocol];
	struct sock *sk;

	rcu_read_lock();
	sk = __netlink_lookup(table, portid, net);
	if (sk)
		sock_hold(sk);
	rcu_read_unlock();

	return sk;
}