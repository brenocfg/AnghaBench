#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_13__ {int preallocate; int prealloc_size; TYPE_3__* inode; int /*<<< orphan*/  formatted_node; TYPE_2__* th; scalar_t__ beg; scalar_t__ search_start; } ;
typedef  TYPE_1__ reiserfs_blocknr_hint_t ;
typedef  scalar_t__ b_blocknr_t ;
struct TYPE_15__ {int /*<<< orphan*/  i_uid; } ;
struct TYPE_14__ {struct super_block* t_super; } ;
struct TYPE_12__ {int i_prealloc_count; } ;

/* Variables and functions */
 int CARRY_ON ; 
 int NO_DISK_SPACE ; 
 int QUOTA_EXCEEDED ; 
 int /*<<< orphan*/  REISERFS_DEBUG_CODE ; 
 TYPE_10__* REISERFS_I (TYPE_3__*) ; 
 scalar_t__ SB_BLOCK_COUNT (struct super_block*) ; 
 int allocate_without_wrapping_disk (TYPE_1__*,scalar_t__*,scalar_t__,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  determine_prealloc_size (TYPE_1__*) ; 
 int dquot_alloc_block_nodirty (TYPE_3__*,int) ; 
 int /*<<< orphan*/  dquot_free_block_nodirty (TYPE_3__*,int) ; 
 int dquot_prealloc_block_nodirty (TYPE_3__*,int) ; 
 int /*<<< orphan*/  reiserfs_debug (struct super_block*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_free_block (TYPE_2__*,TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  reiserfs_write_lock_nested (struct super_block*,int) ; 
 int reiserfs_write_unlock_nested (struct super_block*) ; 

__attribute__((used)) static inline int blocknrs_and_prealloc_arrays_from_search_start
    (reiserfs_blocknr_hint_t * hint, b_blocknr_t * new_blocknrs,
     int amount_needed) {
	struct super_block *s = hint->th->t_super;
	b_blocknr_t start = hint->search_start;
	b_blocknr_t finish = SB_BLOCK_COUNT(s) - 1;
	int passno = 0;
	int nr_allocated = 0;
	int depth;

	determine_prealloc_size(hint);
	if (!hint->formatted_node) {
		int quota_ret;
#ifdef REISERQUOTA_DEBUG
		reiserfs_debug(s, REISERFS_DEBUG_CODE,
			       "reiserquota: allocating %d blocks id=%u",
			       amount_needed, hint->inode->i_uid);
#endif
		depth = reiserfs_write_unlock_nested(s);
		quota_ret =
		    dquot_alloc_block_nodirty(hint->inode, amount_needed);
		if (quota_ret) {	/* Quota exceeded? */
			reiserfs_write_lock_nested(s, depth);
			return QUOTA_EXCEEDED;
		}
		if (hint->preallocate && hint->prealloc_size) {
#ifdef REISERQUOTA_DEBUG
			reiserfs_debug(s, REISERFS_DEBUG_CODE,
				       "reiserquota: allocating (prealloc) %d blocks id=%u",
				       hint->prealloc_size, hint->inode->i_uid);
#endif
			quota_ret = dquot_prealloc_block_nodirty(hint->inode,
							 hint->prealloc_size);
			if (quota_ret)
				hint->preallocate = hint->prealloc_size = 0;
		}
		/* for unformatted nodes, force large allocations */
		reiserfs_write_lock_nested(s, depth);
	}

	do {
		switch (passno++) {
		case 0:	/* Search from hint->search_start to end of disk */
			start = hint->search_start;
			finish = SB_BLOCK_COUNT(s) - 1;
			break;
		case 1:	/* Search from hint->beg to hint->search_start */
			start = hint->beg;
			finish = hint->search_start;
			break;
		case 2:	/* Last chance: Search from 0 to hint->beg */
			start = 0;
			finish = hint->beg;
			break;
		default:
			/* We've tried searching everywhere, not enough space */
			/* Free the blocks */
			if (!hint->formatted_node) {
#ifdef REISERQUOTA_DEBUG
				reiserfs_debug(s, REISERFS_DEBUG_CODE,
					       "reiserquota: freeing (nospace) %d blocks id=%u",
					       amount_needed +
					       hint->prealloc_size -
					       nr_allocated,
					       hint->inode->i_uid);
#endif
				/* Free not allocated blocks */
				depth = reiserfs_write_unlock_nested(s);
				dquot_free_block_nodirty(hint->inode,
					amount_needed + hint->prealloc_size -
					nr_allocated);
				reiserfs_write_lock_nested(s, depth);
			}
			while (nr_allocated--)
				reiserfs_free_block(hint->th, hint->inode,
						    new_blocknrs[nr_allocated],
						    !hint->formatted_node);

			return NO_DISK_SPACE;
		}
	} while ((nr_allocated += allocate_without_wrapping_disk(hint,
								 new_blocknrs +
								 nr_allocated,
								 start, finish,
								 1,
								 amount_needed -
								 nr_allocated,
								 hint->
								 prealloc_size))
		 < amount_needed);
	if (!hint->formatted_node &&
	    amount_needed + hint->prealloc_size >
	    nr_allocated + REISERFS_I(hint->inode)->i_prealloc_count) {
		/* Some of preallocation blocks were not allocated */
#ifdef REISERQUOTA_DEBUG
		reiserfs_debug(s, REISERFS_DEBUG_CODE,
			       "reiserquota: freeing (failed prealloc) %d blocks id=%u",
			       amount_needed + hint->prealloc_size -
			       nr_allocated -
			       REISERFS_I(hint->inode)->i_prealloc_count,
			       hint->inode->i_uid);
#endif

		depth = reiserfs_write_unlock_nested(s);
		dquot_free_block_nodirty(hint->inode, amount_needed +
					 hint->prealloc_size - nr_allocated -
					 REISERFS_I(hint->inode)->
					 i_prealloc_count);
		reiserfs_write_lock_nested(s, depth);
	}

	return CARRY_ON;
}