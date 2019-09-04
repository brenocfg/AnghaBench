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
typedef  scalar_t__ u32 ;
struct ocfs2_dx_entry_list {TYPE_1__* de_entries; int /*<<< orphan*/  de_num_used; } ;
struct ocfs2_dx_leaf {struct ocfs2_dx_entry_list dl_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  dx_major_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOSPC ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int ocfs2_dx_leaf_same_major (struct ocfs2_dx_leaf*) ; 

__attribute__((used)) static int ocfs2_dx_dir_find_leaf_split(struct ocfs2_dx_leaf *dx_leaf,
					u32 leaf_cpos, u32 insert_hash,
					u32 *split_hash)
{
	struct ocfs2_dx_entry_list *dl_list = &dx_leaf->dl_list;
	int i, num_used = le16_to_cpu(dl_list->de_num_used);
	int allsame;

	/*
	 * There's a couple rare, but nasty corner cases we have to
	 * check for here. All of them involve a leaf where all value
	 * have the same hash, which is what we look for first.
	 *
	 * Most of the time, all of the above is false, and we simply
	 * pick the median value for a split.
	 */
	allsame = ocfs2_dx_leaf_same_major(dx_leaf);
	if (allsame) {
		u32 val = le32_to_cpu(dl_list->de_entries[0].dx_major_hash);

		if (val == insert_hash) {
			/*
			 * No matter where we would choose to split,
			 * the new entry would want to occupy the same
			 * block as these. Since there's no space left
			 * in their existing block, we know there
			 * won't be space after the split.
			 */
			return -ENOSPC;
		}

		if (val == leaf_cpos) {
			/*
			 * Because val is the same as leaf_cpos (which
			 * is the smallest value this leaf can have),
			 * yet is not equal to insert_hash, then we
			 * know that insert_hash *must* be larger than
			 * val (and leaf_cpos). At least cpos+1 in value.
			 *
			 * We also know then, that there cannot be an
			 * adjacent extent (otherwise we'd be looking
			 * at it). Choosing this value gives us a
			 * chance to get some contiguousness.
			 */
			*split_hash = leaf_cpos + 1;
			return 0;
		}

		if (val > insert_hash) {
			/*
			 * val can not be the same as insert hash, and
			 * also must be larger than leaf_cpos. Also,
			 * we know that there can't be a leaf between
			 * cpos and val, otherwise the entries with
			 * hash 'val' would be there.
			 */
			*split_hash = val;
			return 0;
		}

		*split_hash = insert_hash;
		return 0;
	}

	/*
	 * Since the records are sorted and the checks above
	 * guaranteed that not all records in this block are the same,
	 * we simple travel forward, from the median, and pick the 1st
	 * record whose value is larger than leaf_cpos.
	 */
	for (i = (num_used / 2); i < num_used; i++)
		if (le32_to_cpu(dl_list->de_entries[i].dx_major_hash) >
		    leaf_cpos)
			break;

	BUG_ON(i == num_used); /* Should be impossible */
	*split_hash = le32_to_cpu(dl_list->de_entries[i].dx_major_hash);
	return 0;
}