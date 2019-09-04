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
 int /*<<< orphan*/  dgram_head ; 
 int /*<<< orphan*/  dgram_lock ; 
 int /*<<< orphan*/  sk_add_node (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dgram_hash(struct sock *sk)
{
	write_lock_bh(&dgram_lock);
	sk_add_node(sk, &dgram_head);
	sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);
	write_unlock_bh(&dgram_lock);

	return 0;
}