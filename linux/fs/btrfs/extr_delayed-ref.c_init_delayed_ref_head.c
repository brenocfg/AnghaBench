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
typedef  void* u64 ;
struct btrfs_qgroup_extent_record {int /*<<< orphan*/ * old_roots; void* num_bytes; void* bytenr; void* data_rsv_refroot; void* data_rsv; } ;
struct btrfs_delayed_ref_head {int ref_mod; int must_insert_reserved; int is_data; int is_system; int total_ref_mod; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; scalar_t__ processing; int /*<<< orphan*/  href_node; int /*<<< orphan*/  ref_add_list; int /*<<< orphan*/  ref_tree; void* num_bytes; void* bytenr; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int BTRFS_ADD_DELAYED_EXTENT ; 
 int BTRFS_DROP_DELAYED_REF ; 
 int BTRFS_UPDATE_DELAYED_HEAD ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_delayed_ref_head(struct btrfs_delayed_ref_head *head_ref,
				  struct btrfs_qgroup_extent_record *qrecord,
				  u64 bytenr, u64 num_bytes, u64 ref_root,
				  u64 reserved, int action, bool is_data,
				  bool is_system)
{
	int count_mod = 1;
	int must_insert_reserved = 0;

	/* If reserved is provided, it must be a data extent. */
	BUG_ON(!is_data && reserved);

	/*
	 * The head node stores the sum of all the mods, so dropping a ref
	 * should drop the sum in the head node by one.
	 */
	if (action == BTRFS_UPDATE_DELAYED_HEAD)
		count_mod = 0;
	else if (action == BTRFS_DROP_DELAYED_REF)
		count_mod = -1;

	/*
	 * BTRFS_ADD_DELAYED_EXTENT means that we need to update the reserved
	 * accounting when the extent is finally added, or if a later
	 * modification deletes the delayed ref without ever inserting the
	 * extent into the extent allocation tree.  ref->must_insert_reserved
	 * is the flag used to record that accounting mods are required.
	 *
	 * Once we record must_insert_reserved, switch the action to
	 * BTRFS_ADD_DELAYED_REF because other special casing is not required.
	 */
	if (action == BTRFS_ADD_DELAYED_EXTENT)
		must_insert_reserved = 1;
	else
		must_insert_reserved = 0;

	refcount_set(&head_ref->refs, 1);
	head_ref->bytenr = bytenr;
	head_ref->num_bytes = num_bytes;
	head_ref->ref_mod = count_mod;
	head_ref->must_insert_reserved = must_insert_reserved;
	head_ref->is_data = is_data;
	head_ref->is_system = is_system;
	head_ref->ref_tree = RB_ROOT_CACHED;
	INIT_LIST_HEAD(&head_ref->ref_add_list);
	RB_CLEAR_NODE(&head_ref->href_node);
	head_ref->processing = 0;
	head_ref->total_ref_mod = count_mod;
	spin_lock_init(&head_ref->lock);
	mutex_init(&head_ref->mutex);

	if (qrecord) {
		if (ref_root && reserved) {
			qrecord->data_rsv = reserved;
			qrecord->data_rsv_refroot = ref_root;
		}
		qrecord->bytenr = bytenr;
		qrecord->num_bytes = num_bytes;
		qrecord->old_roots = NULL;
	}
}