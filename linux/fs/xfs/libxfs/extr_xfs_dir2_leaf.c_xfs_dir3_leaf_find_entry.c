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
struct xfs_dir2_leaf_entry {scalar_t__ address; } ;
typedef  struct xfs_dir2_leaf_entry xfs_dir2_leaf_entry_t ;
struct xfs_dir3_icleaf_hdr {int count; int /*<<< orphan*/  stale; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_DIR2_NULL_DATAPTR ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memmove (struct xfs_dir2_leaf_entry*,struct xfs_dir2_leaf_entry*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_find_stale (struct xfs_dir3_icleaf_hdr*,struct xfs_dir2_leaf_entry*,int,int*,int*) ; 

struct xfs_dir2_leaf_entry *
xfs_dir3_leaf_find_entry(
	struct xfs_dir3_icleaf_hdr *leafhdr,
	struct xfs_dir2_leaf_entry *ents,
	int			index,		/* leaf table position */
	int			compact,	/* need to compact leaves */
	int			lowstale,	/* index of prev stale leaf */
	int			highstale,	/* index of next stale leaf */
	int			*lfloglow,	/* low leaf logging index */
	int			*lfloghigh)	/* high leaf logging index */
{
	if (!leafhdr->stale) {
		xfs_dir2_leaf_entry_t	*lep;	/* leaf entry table pointer */

		/*
		 * Now we need to make room to insert the leaf entry.
		 *
		 * If there are no stale entries, just insert a hole at index.
		 */
		lep = &ents[index];
		if (index < leafhdr->count)
			memmove(lep + 1, lep,
				(leafhdr->count - index) * sizeof(*lep));

		/*
		 * Record low and high logging indices for the leaf.
		 */
		*lfloglow = index;
		*lfloghigh = leafhdr->count++;
		return lep;
	}

	/*
	 * There are stale entries.
	 *
	 * We will use one of them for the new entry.  It's probably not at
	 * the right location, so we'll have to shift some up or down first.
	 *
	 * If we didn't compact before, we need to find the nearest stale
	 * entries before and after our insertion point.
	 */
	if (compact == 0)
		xfs_dir3_leaf_find_stale(leafhdr, ents, index,
					 &lowstale, &highstale);

	/*
	 * If the low one is better, use it.
	 */
	if (lowstale >= 0 &&
	    (highstale == leafhdr->count ||
	     index - lowstale - 1 < highstale - index)) {
		ASSERT(index - lowstale - 1 >= 0);
		ASSERT(ents[lowstale].address ==
		       cpu_to_be32(XFS_DIR2_NULL_DATAPTR));

		/*
		 * Copy entries up to cover the stale entry and make room
		 * for the new entry.
		 */
		if (index - lowstale - 1 > 0) {
			memmove(&ents[lowstale], &ents[lowstale + 1],
				(index - lowstale - 1) *
					sizeof(xfs_dir2_leaf_entry_t));
		}
		*lfloglow = min(lowstale, *lfloglow);
		*lfloghigh = max(index - 1, *lfloghigh);
		leafhdr->stale--;
		return &ents[index - 1];
	}

	/*
	 * The high one is better, so use that one.
	 */
	ASSERT(highstale - index >= 0);
	ASSERT(ents[highstale].address == cpu_to_be32(XFS_DIR2_NULL_DATAPTR));

	/*
	 * Copy entries down to cover the stale entry and make room for the
	 * new entry.
	 */
	if (highstale - index > 0) {
		memmove(&ents[index + 1], &ents[index],
			(highstale - index) * sizeof(xfs_dir2_leaf_entry_t));
	}
	*lfloglow = min(index, *lfloglow);
	*lfloghigh = max(highstale, *lfloghigh);
	leafhdr->stale--;
	return &ents[index];
}