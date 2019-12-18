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
struct sock {int /*<<< orphan*/  sk_omem_alloc; int /*<<< orphan*/  sk_bpf_storage; } ;
struct bpf_sk_storage_map {int dummy; } ;
struct bpf_sk_storage_elem {int dummy; } ;
struct bpf_sk_storage {struct sock* sk; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  __selem_link_sk (struct bpf_sk_storage*,struct bpf_sk_storage_elem*) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 struct bpf_sk_storage* cmpxchg (struct bpf_sk_storage**,int /*<<< orphan*/ *,struct bpf_sk_storage*) ; 
 int /*<<< orphan*/  kfree (struct bpf_sk_storage*) ; 
 struct bpf_sk_storage* kzalloc (int,int) ; 
 int omem_charge (struct sock*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selem_link_map (struct bpf_sk_storage_map*,struct bpf_sk_storage_elem*) ; 
 int /*<<< orphan*/  selem_unlink_map (struct bpf_sk_storage_elem*) ; 
 scalar_t__ unlikely (struct bpf_sk_storage*) ; 

__attribute__((used)) static int sk_storage_alloc(struct sock *sk,
			    struct bpf_sk_storage_map *smap,
			    struct bpf_sk_storage_elem *first_selem)
{
	struct bpf_sk_storage *prev_sk_storage, *sk_storage;
	int err;

	err = omem_charge(sk, sizeof(*sk_storage));
	if (err)
		return err;

	sk_storage = kzalloc(sizeof(*sk_storage), GFP_ATOMIC | __GFP_NOWARN);
	if (!sk_storage) {
		err = -ENOMEM;
		goto uncharge;
	}
	INIT_HLIST_HEAD(&sk_storage->list);
	raw_spin_lock_init(&sk_storage->lock);
	sk_storage->sk = sk;

	__selem_link_sk(sk_storage, first_selem);
	selem_link_map(smap, first_selem);
	/* Publish sk_storage to sk.  sk->sk_lock cannot be acquired.
	 * Hence, atomic ops is used to set sk->sk_bpf_storage
	 * from NULL to the newly allocated sk_storage ptr.
	 *
	 * From now on, the sk->sk_bpf_storage pointer is protected
	 * by the sk_storage->lock.  Hence,  when freeing
	 * the sk->sk_bpf_storage, the sk_storage->lock must
	 * be held before setting sk->sk_bpf_storage to NULL.
	 */
	prev_sk_storage = cmpxchg((struct bpf_sk_storage **)&sk->sk_bpf_storage,
				  NULL, sk_storage);
	if (unlikely(prev_sk_storage)) {
		selem_unlink_map(first_selem);
		err = -EAGAIN;
		goto uncharge;

		/* Note that even first_selem was linked to smap's
		 * bucket->list, first_selem can be freed immediately
		 * (instead of kfree_rcu) because
		 * bpf_sk_storage_map_free() does a
		 * synchronize_rcu() before walking the bucket->list.
		 * Hence, no one is accessing selem from the
		 * bucket->list under rcu_read_lock().
		 */
	}

	return 0;

uncharge:
	kfree(sk_storage);
	atomic_sub(sizeof(*sk_storage), &sk->sk_omem_alloc);
	return err;
}