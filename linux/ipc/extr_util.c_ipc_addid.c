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
struct kern_ipc_perm {int deleted; scalar_t__ key; int /*<<< orphan*/  lock; int /*<<< orphan*/  khtnode; int /*<<< orphan*/  cgid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  cuid; int /*<<< orphan*/  refcount; } ;
struct ipc_ids {int in_use; int max_idx; int /*<<< orphan*/  ipcs_idr; int /*<<< orphan*/  key_ht; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IPC_PRIVATE ; 
 int /*<<< orphan*/  current_euid_egid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int ipc_idr_alloc (struct ipc_ids*,struct kern_ipc_perm*) ; 
 int /*<<< orphan*/  ipc_kht_params ; 
 int ipc_mni ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ipc_addid(struct ipc_ids *ids, struct kern_ipc_perm *new, int limit)
{
	kuid_t euid;
	kgid_t egid;
	int idx, err;

	/* 1) Initialize the refcount so that ipc_rcu_putref works */
	refcount_set(&new->refcount, 1);

	if (limit > ipc_mni)
		limit = ipc_mni;

	if (ids->in_use >= limit)
		return -ENOSPC;

	idr_preload(GFP_KERNEL);

	spin_lock_init(&new->lock);
	rcu_read_lock();
	spin_lock(&new->lock);

	current_euid_egid(&euid, &egid);
	new->cuid = new->uid = euid;
	new->gid = new->cgid = egid;

	new->deleted = false;

	idx = ipc_idr_alloc(ids, new);
	idr_preload_end();

	if (idx >= 0 && new->key != IPC_PRIVATE) {
		err = rhashtable_insert_fast(&ids->key_ht, &new->khtnode,
					     ipc_kht_params);
		if (err < 0) {
			idr_remove(&ids->ipcs_idr, idx);
			idx = err;
		}
	}
	if (idx < 0) {
		new->deleted = true;
		spin_unlock(&new->lock);
		rcu_read_unlock();
		return idx;
	}

	ids->in_use++;
	if (idx > ids->max_idx)
		ids->max_idx = idx;
	return idx;
}