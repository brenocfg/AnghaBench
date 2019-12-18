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
typedef  void* u8 ;
struct batadv_tt_orig_list_entry {int ttvn; int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; void* flags; struct batadv_orig_node* orig_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  vid; } ;
struct batadv_tt_global_entry {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  orig_list_count; int /*<<< orphan*/  orig_list; TYPE_1__ common; } ;
struct batadv_orig_node {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct batadv_tt_orig_list_entry* batadv_tt_global_orig_entry_find (struct batadv_tt_global_entry*,struct batadv_orig_node*) ; 
 int /*<<< orphan*/  batadv_tt_global_size_inc (struct batadv_orig_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tt_global_sync_flags (struct batadv_tt_global_entry*) ; 
 int /*<<< orphan*/  batadv_tt_orig_cache ; 
 int /*<<< orphan*/  batadv_tt_orig_list_entry_put (struct batadv_tt_orig_list_entry*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct batadv_tt_orig_list_entry* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
batadv_tt_global_orig_entry_add(struct batadv_tt_global_entry *tt_global,
				struct batadv_orig_node *orig_node, int ttvn,
				u8 flags)
{
	struct batadv_tt_orig_list_entry *orig_entry;

	spin_lock_bh(&tt_global->list_lock);

	orig_entry = batadv_tt_global_orig_entry_find(tt_global, orig_node);
	if (orig_entry) {
		/* refresh the ttvn: the current value could be a bogus one that
		 * was added during a "temporary client detection"
		 */
		orig_entry->ttvn = ttvn;
		orig_entry->flags = flags;
		goto sync_flags;
	}

	orig_entry = kmem_cache_zalloc(batadv_tt_orig_cache, GFP_ATOMIC);
	if (!orig_entry)
		goto out;

	INIT_HLIST_NODE(&orig_entry->list);
	kref_get(&orig_node->refcount);
	batadv_tt_global_size_inc(orig_node, tt_global->common.vid);
	orig_entry->orig_node = orig_node;
	orig_entry->ttvn = ttvn;
	orig_entry->flags = flags;
	kref_init(&orig_entry->refcount);

	kref_get(&orig_entry->refcount);
	hlist_add_head_rcu(&orig_entry->list,
			   &tt_global->orig_list);
	atomic_inc(&tt_global->orig_list_count);

sync_flags:
	batadv_tt_global_sync_flags(tt_global);
out:
	if (orig_entry)
		batadv_tt_orig_list_entry_put(orig_entry);

	spin_unlock_bh(&tt_global->list_lock);
}