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
struct socket {struct sock* sk; } ;
struct sock {size_t sk_protocol; } ;
struct netlink_table {int dummy; } ;
struct net {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EBUSY ; 
 int S32_MIN ; 
 int /*<<< orphan*/  __netlink_lookup (struct netlink_table*,int,struct net*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 int netlink_insert (struct sock*,int) ; 
 struct netlink_table* nl_table ; 
 int prandom_u32_max (int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct net* sock_net (struct sock*) ; 
 int task_tgid_vnr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netlink_autobind(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct net *net = sock_net(sk);
	struct netlink_table *table = &nl_table[sk->sk_protocol];
	s32 portid = task_tgid_vnr(current);
	int err;
	s32 rover = -4096;
	bool ok;

retry:
	cond_resched();
	rcu_read_lock();
	ok = !__netlink_lookup(table, portid, net);
	rcu_read_unlock();
	if (!ok) {
		/* Bind collision, search negative portid values. */
		if (rover == -4096)
			/* rover will be in range [S32_MIN, -4097] */
			rover = S32_MIN + prandom_u32_max(-4096 - S32_MIN);
		else if (rover >= -4096)
			rover = -4097;
		portid = rover--;
		goto retry;
	}

	err = netlink_insert(sk, portid);
	if (err == -EADDRINUSE)
		goto retry;

	/* If 2 threads race to autobind, that is fine.  */
	if (err == -EBUSY)
		err = 0;

	return err;
}