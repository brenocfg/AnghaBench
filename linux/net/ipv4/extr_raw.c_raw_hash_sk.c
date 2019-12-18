#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {TYPE_2__* sk_prot; } ;
struct raw_hashinfo {int /*<<< orphan*/  lock; struct hlist_head* ht; } ;
struct hlist_head {int dummy; } ;
struct TYPE_6__ {int inet_num; } ;
struct TYPE_4__ {struct raw_hashinfo* raw_hash; } ;
struct TYPE_5__ {TYPE_1__ h; } ;

/* Variables and functions */
 int RAW_HTABLE_SIZE ; 
 TYPE_3__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  sk_add_node (struct sock*,struct hlist_head*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int raw_hash_sk(struct sock *sk)
{
	struct raw_hashinfo *h = sk->sk_prot->h.raw_hash;
	struct hlist_head *head;

	head = &h->ht[inet_sk(sk)->inet_num & (RAW_HTABLE_SIZE - 1)];

	write_lock_bh(&h->lock);
	sk_add_node(sk, head);
	sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);
	write_unlock_bh(&h->lock);

	return 0;
}