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
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
typedef  scalar_t__ xfs_dir2_data_aoff_t ;
struct xfs_dir2_data_unused {scalar_t__ length; } ;
struct xfs_dir2_data_hdr {int dummy; } ;
struct xfs_dir2_data_free {scalar_t__ offset; scalar_t__ length; } ;

/* Variables and functions */
 size_t XFS_DIR2_DATA_FD_COUNT ; 
 int /*<<< orphan*/ * __this_address ; 
 scalar_t__ be16_to_cpu (scalar_t__) ; 
 struct xfs_dir2_data_free* xfs_dir2_data_freefind (struct xfs_dir2_data_hdr*,struct xfs_dir2_data_free*,struct xfs_dir2_data_unused*) ; 

__attribute__((used)) static xfs_failaddr_t
xfs_dir2_data_freefind_verify(
	struct xfs_dir2_data_hdr	*hdr,
	struct xfs_dir2_data_free	*bf,
	struct xfs_dir2_data_unused	*dup,
	struct xfs_dir2_data_free	**bf_ent)
{
	struct xfs_dir2_data_free	*dfp;
	xfs_dir2_data_aoff_t		off;
	bool				matched = false;
	bool				seenzero = false;

	*bf_ent = NULL;
	off = (xfs_dir2_data_aoff_t)((char *)dup - (char *)hdr);

	/*
	 * Validate some consistency in the bestfree table.
	 * Check order, non-overlapping entries, and if we find the
	 * one we're looking for it has to be exact.
	 */
	for (dfp = &bf[0]; dfp < &bf[XFS_DIR2_DATA_FD_COUNT]; dfp++) {
		if (!dfp->offset) {
			if (dfp->length)
				return __this_address;
			seenzero = true;
			continue;
		}
		if (seenzero)
			return __this_address;
		if (be16_to_cpu(dfp->offset) == off) {
			matched = true;
			if (dfp->length != dup->length)
				return __this_address;
		} else if (be16_to_cpu(dfp->offset) > off) {
			if (off + be16_to_cpu(dup->length) >
					be16_to_cpu(dfp->offset))
				return __this_address;
		} else {
			if (be16_to_cpu(dfp->offset) +
					be16_to_cpu(dfp->length) > off)
				return __this_address;
		}
		if (!matched &&
		    be16_to_cpu(dfp->length) < be16_to_cpu(dup->length))
			return __this_address;
		if (dfp > &bf[0] &&
		    be16_to_cpu(dfp[-1].length) < be16_to_cpu(dfp[0].length))
			return __this_address;
	}

	/* Looks ok so far; now try to match up with a bestfree entry. */
	*bf_ent = xfs_dir2_data_freefind(hdr, bf, dup);
	return NULL;
}