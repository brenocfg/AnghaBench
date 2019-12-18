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
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_space_info {int /*<<< orphan*/  flags; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_fs_info {struct btrfs_root* extent_root; } ;

/* Variables and functions */
#define  ALLOC_CHUNK 137 
#define  ALLOC_CHUNK_FORCE 136 
 int /*<<< orphan*/  CHUNK_ALLOC_FORCE ; 
 int /*<<< orphan*/  CHUNK_ALLOC_NO_FORCE ; 
#define  COMMIT_TRANS 135 
 int ENOSPC ; 
#define  FLUSH_DELALLOC 134 
#define  FLUSH_DELALLOC_WAIT 133 
#define  FLUSH_DELAYED_ITEMS 132 
#define  FLUSH_DELAYED_ITEMS_NR 131 
#define  FLUSH_DELAYED_REFS 130 
#define  FLUSH_DELAYED_REFS_NR 129 
 int /*<<< orphan*/  IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
#define  RUN_DELAYED_IPUTS 128 
 int btrfs_chunk_alloc (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*) ; 
 struct btrfs_trans_handle* btrfs_join_transaction (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_metadata_alloc_profile (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_run_delayed_iputs (struct btrfs_fs_info*) ; 
 int btrfs_run_delayed_items_nr (struct btrfs_trans_handle*,int) ; 
 int /*<<< orphan*/  btrfs_run_delayed_refs (struct btrfs_trans_handle*,int) ; 
 int /*<<< orphan*/  btrfs_wait_on_delayed_iputs (struct btrfs_fs_info*) ; 
 int calc_reclaim_items_nr (struct btrfs_fs_info*,int) ; 
 int may_commit_transaction (struct btrfs_fs_info*,struct btrfs_space_info*) ; 
 int /*<<< orphan*/  shrink_delalloc (struct btrfs_fs_info*,int,int,int) ; 
 int /*<<< orphan*/  trace_btrfs_flush_space (struct btrfs_fs_info*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void flush_space(struct btrfs_fs_info *fs_info,
		       struct btrfs_space_info *space_info, u64 num_bytes,
		       int state)
{
	struct btrfs_root *root = fs_info->extent_root;
	struct btrfs_trans_handle *trans;
	int nr;
	int ret = 0;

	switch (state) {
	case FLUSH_DELAYED_ITEMS_NR:
	case FLUSH_DELAYED_ITEMS:
		if (state == FLUSH_DELAYED_ITEMS_NR)
			nr = calc_reclaim_items_nr(fs_info, num_bytes) * 2;
		else
			nr = -1;

		trans = btrfs_join_transaction(root);
		if (IS_ERR(trans)) {
			ret = PTR_ERR(trans);
			break;
		}
		ret = btrfs_run_delayed_items_nr(trans, nr);
		btrfs_end_transaction(trans);
		break;
	case FLUSH_DELALLOC:
	case FLUSH_DELALLOC_WAIT:
		shrink_delalloc(fs_info, num_bytes * 2, num_bytes,
				state == FLUSH_DELALLOC_WAIT);
		break;
	case FLUSH_DELAYED_REFS_NR:
	case FLUSH_DELAYED_REFS:
		trans = btrfs_join_transaction(root);
		if (IS_ERR(trans)) {
			ret = PTR_ERR(trans);
			break;
		}
		if (state == FLUSH_DELAYED_REFS_NR)
			nr = calc_reclaim_items_nr(fs_info, num_bytes);
		else
			nr = 0;
		btrfs_run_delayed_refs(trans, nr);
		btrfs_end_transaction(trans);
		break;
	case ALLOC_CHUNK:
	case ALLOC_CHUNK_FORCE:
		trans = btrfs_join_transaction(root);
		if (IS_ERR(trans)) {
			ret = PTR_ERR(trans);
			break;
		}
		ret = btrfs_chunk_alloc(trans,
				btrfs_metadata_alloc_profile(fs_info),
				(state == ALLOC_CHUNK) ? CHUNK_ALLOC_NO_FORCE :
					CHUNK_ALLOC_FORCE);
		btrfs_end_transaction(trans);
		if (ret > 0 || ret == -ENOSPC)
			ret = 0;
		break;
	case RUN_DELAYED_IPUTS:
		/*
		 * If we have pending delayed iputs then we could free up a
		 * bunch of pinned space, so make sure we run the iputs before
		 * we do our pinned bytes check below.
		 */
		btrfs_run_delayed_iputs(fs_info);
		btrfs_wait_on_delayed_iputs(fs_info);
		break;
	case COMMIT_TRANS:
		ret = may_commit_transaction(fs_info, space_info);
		break;
	default:
		ret = -ENOSPC;
		break;
	}

	trace_btrfs_flush_space(fs_info, space_info->flags, num_bytes, state,
				ret);
	return;
}