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
typedef  scalar_t__ xfs_extlen_t ;
struct xfs_perag {scalar_t__ pagf_freeblks; scalar_t__ pagf_flcount; } ;
struct xfs_alloc_arg {int minlen; int alignment; int minalignslop; scalar_t__ minleft; int maxlen; int /*<<< orphan*/  total; int /*<<< orphan*/  resv; struct xfs_perag* pag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XFS_ALLOC_FLAG_CHECK ; 
 int XFS_ALLOC_FLAG_FREEING ; 
 scalar_t__ max (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ xfs_ag_resv_needed (struct xfs_perag*,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_alloc_longest_free_extent (struct xfs_perag*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool
xfs_alloc_space_available(
	struct xfs_alloc_arg	*args,
	xfs_extlen_t		min_free,
	int			flags)
{
	struct xfs_perag	*pag = args->pag;
	xfs_extlen_t		alloc_len, longest;
	xfs_extlen_t		reservation; /* blocks that are still reserved */
	int			available;

	if (flags & XFS_ALLOC_FLAG_FREEING)
		return true;

	reservation = xfs_ag_resv_needed(pag, args->resv);

	/* do we have enough contiguous free space for the allocation? */
	alloc_len = args->minlen + (args->alignment - 1) + args->minalignslop;
	longest = xfs_alloc_longest_free_extent(pag, min_free, reservation);
	if (longest < alloc_len)
		return false;

	/* do we have enough free space remaining for the allocation? */
	available = (int)(pag->pagf_freeblks + pag->pagf_flcount -
			  reservation - min_free - args->minleft);
	if (available < (int)max(args->total, alloc_len))
		return false;

	/*
	 * Clamp maxlen to the amount of free space available for the actual
	 * extent allocation.
	 */
	if (available < (int)args->maxlen && !(flags & XFS_ALLOC_FLAG_CHECK)) {
		args->maxlen = available;
		ASSERT(args->maxlen > 0);
		ASSERT(args->maxlen >= args->minlen);
	}

	return true;
}