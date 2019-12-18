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
struct bucket {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct bpf_sk_storage_map {int dummy; } ;
struct bpf_sk_storage_elem {int /*<<< orphan*/  map_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  smap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct bpf_sk_storage_map*) ; 
 TYPE_1__* SDATA (struct bpf_sk_storage_elem*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct bucket* select_bucket (struct bpf_sk_storage_map*,struct bpf_sk_storage_elem*) ; 

__attribute__((used)) static void selem_link_map(struct bpf_sk_storage_map *smap,
			   struct bpf_sk_storage_elem *selem)
{
	struct bucket *b = select_bucket(smap, selem);

	raw_spin_lock_bh(&b->lock);
	RCU_INIT_POINTER(SDATA(selem)->smap, smap);
	hlist_add_head_rcu(&selem->map_node, &b->list);
	raw_spin_unlock_bh(&b->lock);
}