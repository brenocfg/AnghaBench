#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {TYPE_2__* sk_prot; } ;
struct hlist_head {int dummy; } ;
struct smc_hashinfo {int /*<<< orphan*/  lock; struct hlist_head ht; } ;
struct TYPE_3__ {struct smc_hashinfo* smc_hash; } ;
struct TYPE_4__ {TYPE_1__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  sk_add_node (struct sock*,struct hlist_head*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int smc_hash_sk(struct sock *sk)
{
	struct smc_hashinfo *h = sk->sk_prot->h.smc_hash;
	struct hlist_head *head;

	head = &h->ht;

	write_lock_bh(&h->lock);
	sk_add_node(sk, head);
	sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);
	write_unlock_bh(&h->lock);

	return 0;
}