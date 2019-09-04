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
typedef  int /*<<< orphan*/  xfs_dir2_leaf_entry_t ;
typedef  int /*<<< orphan*/  xfs_da_args_t ;
struct xfs_dir3_icleaf_hdr {int count; int stale; } ;
struct xfs_dir2_leaf_entry {scalar_t__ address; } ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DIR2_NULL_DATAPTR ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct xfs_dir2_leaf_entry*,struct xfs_dir2_leaf_entry*,int) ; 
 int /*<<< orphan*/  memmove (struct xfs_dir2_leaf_entry*,struct xfs_dir2_leaf_entry*,int) ; 
 int /*<<< orphan*/  trace_xfs_dir2_leafn_moveents (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_ents (int /*<<< orphan*/ *,struct xfs_buf*,int,int) ; 

__attribute__((used)) static void
xfs_dir3_leafn_moveents(
	xfs_da_args_t			*args,	/* operation arguments */
	struct xfs_buf			*bp_s,	/* source */
	struct xfs_dir3_icleaf_hdr	*shdr,
	struct xfs_dir2_leaf_entry	*sents,
	int				start_s,/* source leaf index */
	struct xfs_buf			*bp_d,	/* destination */
	struct xfs_dir3_icleaf_hdr	*dhdr,
	struct xfs_dir2_leaf_entry	*dents,
	int				start_d,/* destination leaf index */
	int				count)	/* count of leaves to copy */
{
	int				stale;	/* count stale leaves copied */

	trace_xfs_dir2_leafn_moveents(args, start_s, start_d, count);

	/*
	 * Silently return if nothing to do.
	 */
	if (count == 0)
		return;

	/*
	 * If the destination index is not the end of the current
	 * destination leaf entries, open up a hole in the destination
	 * to hold the new entries.
	 */
	if (start_d < dhdr->count) {
		memmove(&dents[start_d + count], &dents[start_d],
			(dhdr->count - start_d) * sizeof(xfs_dir2_leaf_entry_t));
		xfs_dir3_leaf_log_ents(args, bp_d, start_d + count,
				       count + dhdr->count - 1);
	}
	/*
	 * If the source has stale leaves, count the ones in the copy range
	 * so we can update the header correctly.
	 */
	if (shdr->stale) {
		int	i;			/* temp leaf index */

		for (i = start_s, stale = 0; i < start_s + count; i++) {
			if (sents[i].address ==
					cpu_to_be32(XFS_DIR2_NULL_DATAPTR))
				stale++;
		}
	} else
		stale = 0;
	/*
	 * Copy the leaf entries from source to destination.
	 */
	memcpy(&dents[start_d], &sents[start_s],
		count * sizeof(xfs_dir2_leaf_entry_t));
	xfs_dir3_leaf_log_ents(args, bp_d, start_d, start_d + count - 1);

	/*
	 * If there are source entries after the ones we copied,
	 * delete the ones we copied by sliding the next ones down.
	 */
	if (start_s + count < shdr->count) {
		memmove(&sents[start_s], &sents[start_s + count],
			count * sizeof(xfs_dir2_leaf_entry_t));
		xfs_dir3_leaf_log_ents(args, bp_s, start_s, start_s + count - 1);
	}

	/*
	 * Update the headers and log them.
	 */
	shdr->count -= count;
	shdr->stale -= stale;
	dhdr->count += count;
	dhdr->stale += stale;
}