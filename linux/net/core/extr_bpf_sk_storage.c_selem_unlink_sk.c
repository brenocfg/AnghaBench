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
struct bpf_sk_storage_elem {int /*<<< orphan*/  sk_storage; } ;
struct bpf_sk_storage {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __selem_unlink_sk (struct bpf_sk_storage*,struct bpf_sk_storage_elem*,int) ; 
 int /*<<< orphan*/  kfree_rcu (struct bpf_sk_storage*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 
 struct bpf_sk_storage* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selem_linked_to_sk (struct bpf_sk_storage_elem*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void selem_unlink_sk(struct bpf_sk_storage_elem *selem)
{
	struct bpf_sk_storage *sk_storage;
	bool free_sk_storage = false;

	if (unlikely(!selem_linked_to_sk(selem)))
		/* selem has already been unlinked from sk */
		return;

	sk_storage = rcu_dereference(selem->sk_storage);
	raw_spin_lock_bh(&sk_storage->lock);
	if (likely(selem_linked_to_sk(selem)))
		free_sk_storage = __selem_unlink_sk(sk_storage, selem, true);
	raw_spin_unlock_bh(&sk_storage->lock);

	if (free_sk_storage)
		kfree_rcu(sk_storage, rcu);
}