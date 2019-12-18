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
struct sock {int /*<<< orphan*/  sk_prot; int /*<<< orphan*/  sk_hash; } ;
struct inet_timewait_sock {int /*<<< orphan*/  tw_refcnt; TYPE_1__* tw_tb; } ;
struct inet_sock {int /*<<< orphan*/  inet_num; } ;
struct inet_hashinfo {int /*<<< orphan*/  bhash_size; struct inet_bind_hashbucket* bhash; } ;
struct inet_ehash_bucket {int /*<<< orphan*/  chain; } ;
struct inet_connection_sock {TYPE_1__* icsk_bind_hash; } ;
struct inet_bind_hashbucket {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_2__ {int /*<<< orphan*/  owners; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ __sk_nulls_del_node_init_rcu (struct sock*) ; 
 size_t inet_bhashfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 struct inet_ehash_bucket* inet_ehash_bucket (struct inet_hashinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * inet_ehash_lockp (struct inet_hashinfo*,int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  inet_twsk_add_bind_node (struct inet_timewait_sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet_twsk_add_node_rcu (struct inet_timewait_sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  twsk_net (struct inet_timewait_sock*) ; 

void inet_twsk_hashdance(struct inet_timewait_sock *tw, struct sock *sk,
			   struct inet_hashinfo *hashinfo)
{
	const struct inet_sock *inet = inet_sk(sk);
	const struct inet_connection_sock *icsk = inet_csk(sk);
	struct inet_ehash_bucket *ehead = inet_ehash_bucket(hashinfo, sk->sk_hash);
	spinlock_t *lock = inet_ehash_lockp(hashinfo, sk->sk_hash);
	struct inet_bind_hashbucket *bhead;
	/* Step 1: Put TW into bind hash. Original socket stays there too.
	   Note, that any socket with inet->num != 0 MUST be bound in
	   binding cache, even if it is closed.
	 */
	bhead = &hashinfo->bhash[inet_bhashfn(twsk_net(tw), inet->inet_num,
			hashinfo->bhash_size)];
	spin_lock(&bhead->lock);
	tw->tw_tb = icsk->icsk_bind_hash;
	WARN_ON(!icsk->icsk_bind_hash);
	inet_twsk_add_bind_node(tw, &tw->tw_tb->owners);
	spin_unlock(&bhead->lock);

	spin_lock(lock);

	inet_twsk_add_node_rcu(tw, &ehead->chain);

	/* Step 3: Remove SK from hash chain */
	if (__sk_nulls_del_node_init_rcu(sk))
		sock_prot_inuse_add(sock_net(sk), sk->sk_prot, -1);

	spin_unlock(lock);

	/* tw_refcnt is set to 3 because we have :
	 * - one reference for bhash chain.
	 * - one reference for ehash chain.
	 * - one reference for timer.
	 * We can use atomic_set() because prior spin_lock()/spin_unlock()
	 * committed into memory all tw fields.
	 * Also note that after this point, we lost our implicit reference
	 * so we are not allowed to use tw anymore.
	 */
	refcount_set(&tw->tw_refcnt, 3);
}