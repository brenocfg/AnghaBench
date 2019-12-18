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
struct unix_sock {scalar_t__ addr; } ;
struct sock {int sk_socket; int /*<<< orphan*/  sk_prot; int /*<<< orphan*/  sk_wmem_alloc; int /*<<< orphan*/  sk_receive_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  pr_debug (char*,struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,struct sock*) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_unhashed (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unix_nr_socks ; 
 int /*<<< orphan*/  unix_release_addr (scalar_t__) ; 
 struct unix_sock* unix_sk (struct sock*) ; 

__attribute__((used)) static void unix_sock_destructor(struct sock *sk)
{
	struct unix_sock *u = unix_sk(sk);

	skb_queue_purge(&sk->sk_receive_queue);

	WARN_ON(refcount_read(&sk->sk_wmem_alloc));
	WARN_ON(!sk_unhashed(sk));
	WARN_ON(sk->sk_socket);
	if (!sock_flag(sk, SOCK_DEAD)) {
		pr_info("Attempt to release alive unix socket: %p\n", sk);
		return;
	}

	if (u->addr)
		unix_release_addr(u->addr);

	atomic_long_dec(&unix_nr_socks);
	local_bh_disable();
	sock_prot_inuse_add(sock_net(sk), sk->sk_prot, -1);
	local_bh_enable();
#ifdef UNIX_REFCNT_DEBUG
	pr_debug("UNIX %p is destroyed, %ld are still alive.\n", sk,
		atomic_long_read(&unix_nr_socks));
#endif
}