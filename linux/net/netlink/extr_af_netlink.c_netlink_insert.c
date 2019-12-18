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
typedef  scalar_t__ u32 ;
struct sock {size_t sk_protocol; } ;
struct netlink_table {int dummy; } ;
struct TYPE_2__ {scalar_t__ portid; scalar_t__ bound; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EBUSY ; 
 int EEXIST ; 
 int EOVERFLOW ; 
 int __netlink_insert (struct netlink_table*,struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 struct netlink_table* nl_table ; 
 TYPE_1__* nlk_sk (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int netlink_insert(struct sock *sk, u32 portid)
{
	struct netlink_table *table = &nl_table[sk->sk_protocol];
	int err;

	lock_sock(sk);

	err = nlk_sk(sk)->portid == portid ? 0 : -EBUSY;
	if (nlk_sk(sk)->bound)
		goto err;

	nlk_sk(sk)->portid = portid;
	sock_hold(sk);

	err = __netlink_insert(table, sk);
	if (err) {
		/* In case the hashtable backend returns with -EBUSY
		 * from here, it must not escape to the caller.
		 */
		if (unlikely(err == -EBUSY))
			err = -EOVERFLOW;
		if (err == -EEXIST)
			err = -EADDRINUSE;
		sock_put(sk);
		goto err;
	}

	/* We need to ensure that the socket is hashed and visible. */
	smp_wmb();
	nlk_sk(sk)->bound = portid;

err:
	release_sock(sk);
	return err;
}