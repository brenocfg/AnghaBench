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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u64 ;
struct btrfs_fs_info {int /*<<< orphan*/  tree_mod_seq; } ;
struct btrfs_delayed_ref_node {int ref_mod; int action; int in_tree; int /*<<< orphan*/  add_list; int /*<<< orphan*/  ref_node; int /*<<< orphan*/  type; void* seq; scalar_t__ is_head; void* num_bytes; void* bytenr; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int BTRFS_ADD_DELAYED_EXTENT ; 
 int BTRFS_ADD_DELAYED_REF ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 void* atomic64_read (int /*<<< orphan*/ *) ; 
 scalar_t__ is_fstree (void*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void init_delayed_ref_common(struct btrfs_fs_info *fs_info,
				    struct btrfs_delayed_ref_node *ref,
				    u64 bytenr, u64 num_bytes, u64 ref_root,
				    int action, u8 ref_type)
{
	u64 seq = 0;

	if (action == BTRFS_ADD_DELAYED_EXTENT)
		action = BTRFS_ADD_DELAYED_REF;

	if (is_fstree(ref_root))
		seq = atomic64_read(&fs_info->tree_mod_seq);

	refcount_set(&ref->refs, 1);
	ref->bytenr = bytenr;
	ref->num_bytes = num_bytes;
	ref->ref_mod = 1;
	ref->action = action;
	ref->is_head = 0;
	ref->in_tree = 1;
	ref->seq = seq;
	ref->type = ref_type;
	RB_CLEAR_NODE(&ref->ref_node);
	INIT_LIST_HEAD(&ref->add_list);
}