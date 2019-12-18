#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_bpf_storage; int /*<<< orphan*/  sk_omem_alloc; } ;
struct bpf_sk_storage_map {int elem_size; size_t cache_idx; } ;
struct bpf_sk_storage_elem {int /*<<< orphan*/  snode; } ;
struct bpf_sk_storage {int /*<<< orphan*/ * cache; struct sock* sk; int /*<<< orphan*/  list; } ;
struct TYPE_3__ {int /*<<< orphan*/  smap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* SDATA (struct bpf_sk_storage_elem*) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int hlist_is_singular_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct bpf_sk_storage_elem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 TYPE_1__* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 struct bpf_sk_storage_map* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __selem_unlink_sk(struct bpf_sk_storage *sk_storage,
			      struct bpf_sk_storage_elem *selem,
			      bool uncharge_omem)
{
	struct bpf_sk_storage_map *smap;
	bool free_sk_storage;
	struct sock *sk;

	smap = rcu_dereference(SDATA(selem)->smap);
	sk = sk_storage->sk;

	/* All uncharging on sk->sk_omem_alloc must be done first.
	 * sk may be freed once the last selem is unlinked from sk_storage.
	 */
	if (uncharge_omem)
		atomic_sub(smap->elem_size, &sk->sk_omem_alloc);

	free_sk_storage = hlist_is_singular_node(&selem->snode,
						 &sk_storage->list);
	if (free_sk_storage) {
		atomic_sub(sizeof(struct bpf_sk_storage), &sk->sk_omem_alloc);
		sk_storage->sk = NULL;
		/* After this RCU_INIT, sk may be freed and cannot be used */
		RCU_INIT_POINTER(sk->sk_bpf_storage, NULL);

		/* sk_storage is not freed now.  sk_storage->lock is
		 * still held and raw_spin_unlock_bh(&sk_storage->lock)
		 * will be done by the caller.
		 *
		 * Although the unlock will be done under
		 * rcu_read_lock(),  it is more intutivie to
		 * read if kfree_rcu(sk_storage, rcu) is done
		 * after the raw_spin_unlock_bh(&sk_storage->lock).
		 *
		 * Hence, a "bool free_sk_storage" is returned
		 * to the caller which then calls the kfree_rcu()
		 * after unlock.
		 */
	}
	hlist_del_init_rcu(&selem->snode);
	if (rcu_access_pointer(sk_storage->cache[smap->cache_idx]) ==
	    SDATA(selem))
		RCU_INIT_POINTER(sk_storage->cache[smap->cache_idx], NULL);

	kfree_rcu(selem, rcu);

	return free_sk_storage;
}