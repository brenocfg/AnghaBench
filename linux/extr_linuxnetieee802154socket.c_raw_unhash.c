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
struct sock {int /*<<< orphan*/  sk_prot; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw_lock ; 
 scalar_t__ sk_del_node_init (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raw_unhash(struct sock *sk)
{
	write_lock_bh(&raw_lock);
	if (sk_del_node_init(sk))
		sock_prot_inuse_add(sock_net(sk), sk->sk_prot, -1);
	write_unlock_bh(&raw_lock);
}