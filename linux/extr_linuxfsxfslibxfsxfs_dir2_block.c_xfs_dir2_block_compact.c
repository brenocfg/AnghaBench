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
typedef  int /*<<< orphan*/  xfs_dir2_data_aoff_t ;
struct xfs_dir2_leaf_entry {scalar_t__ address; } ;
struct xfs_dir2_data_hdr {int dummy; } ;
struct xfs_dir2_block_tail {scalar_t__ stale; scalar_t__ count; } ;
struct xfs_da_args {int /*<<< orphan*/  dp; } ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int XFS_DIR2_NULL_DATAPTR ; 
 int /*<<< orphan*/  be32_add_cpu (scalar_t__*,int) ; 
 int be32_to_cpu (scalar_t__) ; 
 scalar_t__ cpu_to_be32 (int) ; 
 int /*<<< orphan*/  xfs_dir2_data_freescan (int /*<<< orphan*/ ,struct xfs_dir2_data_hdr*,int*) ; 
 int /*<<< orphan*/  xfs_dir2_data_make_free (struct xfs_da_args*,struct xfs_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void
xfs_dir2_block_compact(
	struct xfs_da_args		*args,
	struct xfs_buf			*bp,
	struct xfs_dir2_data_hdr	*hdr,
	struct xfs_dir2_block_tail	*btp,
	struct xfs_dir2_leaf_entry	*blp,
	int				*needlog,
	int				*lfloghigh,
	int				*lfloglow)
{
	int			fromidx;	/* source leaf index */
	int			toidx;		/* target leaf index */
	int			needscan = 0;
	int			highstale;	/* high stale index */

	fromidx = toidx = be32_to_cpu(btp->count) - 1;
	highstale = *lfloghigh = -1;
	for (; fromidx >= 0; fromidx--) {
		if (blp[fromidx].address == cpu_to_be32(XFS_DIR2_NULL_DATAPTR)) {
			if (highstale == -1)
				highstale = toidx;
			else {
				if (*lfloghigh == -1)
					*lfloghigh = toidx;
				continue;
			}
		}
		if (fromidx < toidx)
			blp[toidx] = blp[fromidx];
		toidx--;
	}
	*lfloglow = toidx + 1 - (be32_to_cpu(btp->stale) - 1);
	*lfloghigh -= be32_to_cpu(btp->stale) - 1;
	be32_add_cpu(&btp->count, -(be32_to_cpu(btp->stale) - 1));
	xfs_dir2_data_make_free(args, bp,
		(xfs_dir2_data_aoff_t)((char *)blp - (char *)hdr),
		(xfs_dir2_data_aoff_t)((be32_to_cpu(btp->stale) - 1) * sizeof(*blp)),
		needlog, &needscan);
	btp->stale = cpu_to_be32(1);
	/*
	 * If we now need to rebuild the bestfree map, do so.
	 * This needs to happen before the next call to use_free.
	 */
	if (needscan)
		xfs_dir2_data_freescan(args->dp, hdr, needlog);
}