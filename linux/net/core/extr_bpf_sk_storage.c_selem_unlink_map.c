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
struct bucket {int /*<<< orphan*/  lock; } ;
struct bpf_sk_storage_map {int dummy; } ;
struct bpf_sk_storage_elem {int /*<<< orphan*/  map_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  smap; } ;

/* Variables and functions */
 TYPE_1__* SDATA (struct bpf_sk_storage_elem*) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct bpf_sk_storage_map* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct bucket* select_bucket (struct bpf_sk_storage_map*,struct bpf_sk_storage_elem*) ; 
 int /*<<< orphan*/  selem_linked_to_map (struct bpf_sk_storage_elem*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void selem_unlink_map(struct bpf_sk_storage_elem *selem)
{
	struct bpf_sk_storage_map *smap;
	struct bucket *b;

	if (unlikely(!selem_linked_to_map(selem)))
		/* selem has already be unlinked from smap */
		return;

	smap = rcu_dereference(SDATA(selem)->smap);
	b = select_bucket(smap, selem);
	raw_spin_lock_bh(&b->lock);
	if (likely(selem_linked_to_map(selem)))
		hlist_del_init_rcu(&selem->map_node);
	raw_spin_unlock_bh(&b->lock);
}