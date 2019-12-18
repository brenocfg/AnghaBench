#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {TYPE_2__* sk_prot; } ;
struct inet_hashinfo {int /*<<< orphan*/  bind_bucket_cachep; struct inet_bind_hashbucket* bhash; int /*<<< orphan*/  bhash_size; } ;
struct inet_bind_hashbucket {int /*<<< orphan*/  lock; } ;
struct inet_bind_bucket {int dummy; } ;
struct TYPE_8__ {struct inet_bind_bucket* icsk_bind_hash; } ;
struct TYPE_7__ {scalar_t__ inet_num; } ;
struct TYPE_5__ {struct inet_hashinfo* hashinfo; } ;
struct TYPE_6__ {TYPE_1__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sk_del_bind_node (struct sock*) ; 
 int inet_bhashfn (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_bind_bucket_destroy (int /*<<< orphan*/ ,struct inet_bind_bucket*) ; 
 TYPE_4__* inet_csk (struct sock*) ; 
 TYPE_3__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __inet_put_port(struct sock *sk)
{
	struct inet_hashinfo *hashinfo = sk->sk_prot->h.hashinfo;
	const int bhash = inet_bhashfn(sock_net(sk), inet_sk(sk)->inet_num,
			hashinfo->bhash_size);
	struct inet_bind_hashbucket *head = &hashinfo->bhash[bhash];
	struct inet_bind_bucket *tb;

	spin_lock(&head->lock);
	tb = inet_csk(sk)->icsk_bind_hash;
	__sk_del_bind_node(sk);
	inet_csk(sk)->icsk_bind_hash = NULL;
	inet_sk(sk)->inet_num = 0;
	inet_bind_bucket_destroy(hashinfo->bind_bucket_cachep, tb);
	spin_unlock(&head->lock);
}