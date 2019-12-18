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
struct sock {int dummy; } ;
struct inet_timewait_sock {TYPE_1__* tw_dr; int /*<<< orphan*/  tw_num; int /*<<< orphan*/  tw_hash; } ;
struct inet_hashinfo {int /*<<< orphan*/  bhash_size; struct inet_bind_hashbucket* bhash; } ;
struct inet_bind_hashbucket {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_2__ {int /*<<< orphan*/  tw_count; struct inet_hashinfo* hashinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 size_t inet_bhashfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * inet_ehash_lockp (struct inet_hashinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_twsk_bind_unhash (struct inet_timewait_sock*,struct inet_hashinfo*) ; 
 int /*<<< orphan*/  inet_twsk_put (struct inet_timewait_sock*) ; 
 int /*<<< orphan*/  sk_nulls_del_node_init_rcu (struct sock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  twsk_net (struct inet_timewait_sock*) ; 

__attribute__((used)) static void inet_twsk_kill(struct inet_timewait_sock *tw)
{
	struct inet_hashinfo *hashinfo = tw->tw_dr->hashinfo;
	spinlock_t *lock = inet_ehash_lockp(hashinfo, tw->tw_hash);
	struct inet_bind_hashbucket *bhead;

	spin_lock(lock);
	sk_nulls_del_node_init_rcu((struct sock *)tw);
	spin_unlock(lock);

	/* Disassociate with bind bucket. */
	bhead = &hashinfo->bhash[inet_bhashfn(twsk_net(tw), tw->tw_num,
			hashinfo->bhash_size)];

	spin_lock(&bhead->lock);
	inet_twsk_bind_unhash(tw, hashinfo);
	spin_unlock(&bhead->lock);

	atomic_dec(&tw->tw_dr->tw_count);
	inet_twsk_put(tw);
}