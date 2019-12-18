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
typedef  int u64 ;
struct sock {int /*<<< orphan*/  sk_omem_alloc; int /*<<< orphan*/  sk_bpf_storage; } ;
struct bpf_sk_storage_map {int /*<<< orphan*/  elem_size; } ;
struct bpf_sk_storage_elem {int dummy; } ;
struct bpf_sk_storage_data {int /*<<< orphan*/  data; } ;
struct bpf_sk_storage {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int BPF_EXIST ; 
 int BPF_F_LOCK ; 
 int BPF_NOEXIST ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct bpf_sk_storage_data* ERR_PTR (int) ; 
 struct bpf_sk_storage_data* SDATA (struct bpf_sk_storage_elem*) ; 
 struct bpf_sk_storage_elem* SELEM (struct bpf_sk_storage_data*) ; 
 int /*<<< orphan*/  __selem_link_sk (struct bpf_sk_storage*,struct bpf_sk_storage_elem*) ; 
 int /*<<< orphan*/  __selem_unlink_sk (struct bpf_sk_storage*,struct bpf_sk_storage_elem*,int) ; 
 struct bpf_sk_storage_data* __sk_storage_lookup (struct bpf_sk_storage*,struct bpf_sk_storage_map*,int) ; 
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int check_flags (struct bpf_sk_storage_data*,int) ; 
 int /*<<< orphan*/  copy_map_value_locked (struct bpf_map*,int /*<<< orphan*/ ,void*,int) ; 
 int hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bpf_sk_storage_elem*) ; 
 int /*<<< orphan*/  map_value_has_spin_lock (struct bpf_map*) ; 
 int /*<<< orphan*/  raw_spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct bpf_sk_storage* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct bpf_sk_storage_elem* selem_alloc (struct bpf_sk_storage_map*,struct sock*,void*,int) ; 
 int /*<<< orphan*/  selem_link_map (struct bpf_sk_storage_map*,struct bpf_sk_storage_elem*) ; 
 scalar_t__ selem_linked_to_sk (struct bpf_sk_storage_elem*) ; 
 int /*<<< orphan*/  selem_unlink_map (struct bpf_sk_storage_elem*) ; 
 int sk_storage_alloc (struct sock*,struct bpf_sk_storage_map*,struct bpf_sk_storage_elem*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct bpf_sk_storage_data *sk_storage_update(struct sock *sk,
						     struct bpf_map *map,
						     void *value,
						     u64 map_flags)
{
	struct bpf_sk_storage_data *old_sdata = NULL;
	struct bpf_sk_storage_elem *selem;
	struct bpf_sk_storage *sk_storage;
	struct bpf_sk_storage_map *smap;
	int err;

	/* BPF_EXIST and BPF_NOEXIST cannot be both set */
	if (unlikely((map_flags & ~BPF_F_LOCK) > BPF_EXIST) ||
	    /* BPF_F_LOCK can only be used in a value with spin_lock */
	    unlikely((map_flags & BPF_F_LOCK) && !map_value_has_spin_lock(map)))
		return ERR_PTR(-EINVAL);

	smap = (struct bpf_sk_storage_map *)map;
	sk_storage = rcu_dereference(sk->sk_bpf_storage);
	if (!sk_storage || hlist_empty(&sk_storage->list)) {
		/* Very first elem for this sk */
		err = check_flags(NULL, map_flags);
		if (err)
			return ERR_PTR(err);

		selem = selem_alloc(smap, sk, value, true);
		if (!selem)
			return ERR_PTR(-ENOMEM);

		err = sk_storage_alloc(sk, smap, selem);
		if (err) {
			kfree(selem);
			atomic_sub(smap->elem_size, &sk->sk_omem_alloc);
			return ERR_PTR(err);
		}

		return SDATA(selem);
	}

	if ((map_flags & BPF_F_LOCK) && !(map_flags & BPF_NOEXIST)) {
		/* Hoping to find an old_sdata to do inline update
		 * such that it can avoid taking the sk_storage->lock
		 * and changing the lists.
		 */
		old_sdata = __sk_storage_lookup(sk_storage, smap, false);
		err = check_flags(old_sdata, map_flags);
		if (err)
			return ERR_PTR(err);
		if (old_sdata && selem_linked_to_sk(SELEM(old_sdata))) {
			copy_map_value_locked(map, old_sdata->data,
					      value, false);
			return old_sdata;
		}
	}

	raw_spin_lock_bh(&sk_storage->lock);

	/* Recheck sk_storage->list under sk_storage->lock */
	if (unlikely(hlist_empty(&sk_storage->list))) {
		/* A parallel del is happening and sk_storage is going
		 * away.  It has just been checked before, so very
		 * unlikely.  Return instead of retry to keep things
		 * simple.
		 */
		err = -EAGAIN;
		goto unlock_err;
	}

	old_sdata = __sk_storage_lookup(sk_storage, smap, false);
	err = check_flags(old_sdata, map_flags);
	if (err)
		goto unlock_err;

	if (old_sdata && (map_flags & BPF_F_LOCK)) {
		copy_map_value_locked(map, old_sdata->data, value, false);
		selem = SELEM(old_sdata);
		goto unlock;
	}

	/* sk_storage->lock is held.  Hence, we are sure
	 * we can unlink and uncharge the old_sdata successfully
	 * later.  Hence, instead of charging the new selem now
	 * and then uncharge the old selem later (which may cause
	 * a potential but unnecessary charge failure),  avoid taking
	 * a charge at all here (the "!old_sdata" check) and the
	 * old_sdata will not be uncharged later during __selem_unlink_sk().
	 */
	selem = selem_alloc(smap, sk, value, !old_sdata);
	if (!selem) {
		err = -ENOMEM;
		goto unlock_err;
	}

	/* First, link the new selem to the map */
	selem_link_map(smap, selem);

	/* Second, link (and publish) the new selem to sk_storage */
	__selem_link_sk(sk_storage, selem);

	/* Third, remove old selem, SELEM(old_sdata) */
	if (old_sdata) {
		selem_unlink_map(SELEM(old_sdata));
		__selem_unlink_sk(sk_storage, SELEM(old_sdata), false);
	}

unlock:
	raw_spin_unlock_bh(&sk_storage->lock);
	return SDATA(selem);

unlock_err:
	raw_spin_unlock_bh(&sk_storage->lock);
	return ERR_PTR(err);
}