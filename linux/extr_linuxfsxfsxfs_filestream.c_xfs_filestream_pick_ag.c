#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_extlen_t ;
typedef  scalar_t__ xfs_agnumber_t ;
struct xfs_perag {scalar_t__ pagf_freeblks; int /*<<< orphan*/  pagf_metadata; int /*<<< orphan*/  pagf_init; } ;
struct TYPE_3__ {int sb_agblocks; scalar_t__ sb_agcount; } ;
struct xfs_mount {int /*<<< orphan*/  m_filestream; TYPE_1__ m_sb; } ;
struct xfs_inode {int /*<<< orphan*/  i_ino; struct xfs_mount* i_mount; } ;
struct xfs_fstrm_item {int /*<<< orphan*/  mru; scalar_t__ ag; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KM_MAYFAIL ; 
 scalar_t__ NULLAGNUMBER ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 TYPE_2__* VFS_I (struct xfs_inode*) ; 
 int /*<<< orphan*/  XFS_AG_RESV_NONE ; 
 int XFS_ALLOC_FLAG_TRYLOCK ; 
 int XFS_PICK_LOWSPACE ; 
 int XFS_PICK_USERDATA ; 
 struct xfs_fstrm_item* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (struct xfs_fstrm_item*) ; 
 int /*<<< orphan*/  trace_xfs_filestream_pick (struct xfs_inode*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  trace_xfs_filestream_scan (struct xfs_mount*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xfs_ag_resv_needed (struct xfs_perag*,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_alloc_longest_free_extent (struct xfs_perag*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_alloc_min_freelist (struct xfs_mount*,struct xfs_perag*) ; 
 int xfs_alloc_pagf_init (struct xfs_mount*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int xfs_filestream_get_ag (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_filestream_put_ag (struct xfs_mount*,scalar_t__) ; 
 int xfs_mru_cache_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct xfs_perag* xfs_perag_get (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_perag_put (struct xfs_perag*) ; 

__attribute__((used)) static int
xfs_filestream_pick_ag(
	struct xfs_inode	*ip,
	xfs_agnumber_t		startag,
	xfs_agnumber_t		*agp,
	int			flags,
	xfs_extlen_t		minlen)
{
	struct xfs_mount	*mp = ip->i_mount;
	struct xfs_fstrm_item	*item;
	struct xfs_perag	*pag;
	xfs_extlen_t		longest, free = 0, minfree, maxfree = 0;
	xfs_agnumber_t		ag, max_ag = NULLAGNUMBER;
	int			err, trylock, nscan;

	ASSERT(S_ISDIR(VFS_I(ip)->i_mode));

	/* 2% of an AG's blocks must be free for it to be chosen. */
	minfree = mp->m_sb.sb_agblocks / 50;

	ag = startag;
	*agp = NULLAGNUMBER;

	/* For the first pass, don't sleep trying to init the per-AG. */
	trylock = XFS_ALLOC_FLAG_TRYLOCK;

	for (nscan = 0; 1; nscan++) {
		trace_xfs_filestream_scan(mp, ip->i_ino, ag);

		pag = xfs_perag_get(mp, ag);

		if (!pag->pagf_init) {
			err = xfs_alloc_pagf_init(mp, NULL, ag, trylock);
			if (err && !trylock) {
				xfs_perag_put(pag);
				return err;
			}
		}

		/* Might fail sometimes during the 1st pass with trylock set. */
		if (!pag->pagf_init)
			goto next_ag;

		/* Keep track of the AG with the most free blocks. */
		if (pag->pagf_freeblks > maxfree) {
			maxfree = pag->pagf_freeblks;
			max_ag = ag;
		}

		/*
		 * The AG reference count does two things: it enforces mutual
		 * exclusion when examining the suitability of an AG in this
		 * loop, and it guards against two filestreams being established
		 * in the same AG as each other.
		 */
		if (xfs_filestream_get_ag(mp, ag) > 1) {
			xfs_filestream_put_ag(mp, ag);
			goto next_ag;
		}

		longest = xfs_alloc_longest_free_extent(pag,
				xfs_alloc_min_freelist(mp, pag),
				xfs_ag_resv_needed(pag, XFS_AG_RESV_NONE));
		if (((minlen && longest >= minlen) ||
		     (!minlen && pag->pagf_freeblks >= minfree)) &&
		    (!pag->pagf_metadata || !(flags & XFS_PICK_USERDATA) ||
		     (flags & XFS_PICK_LOWSPACE))) {

			/* Break out, retaining the reference on the AG. */
			free = pag->pagf_freeblks;
			xfs_perag_put(pag);
			*agp = ag;
			break;
		}

		/* Drop the reference on this AG, it's not usable. */
		xfs_filestream_put_ag(mp, ag);
next_ag:
		xfs_perag_put(pag);
		/* Move to the next AG, wrapping to AG 0 if necessary. */
		if (++ag >= mp->m_sb.sb_agcount)
			ag = 0;

		/* If a full pass of the AGs hasn't been done yet, continue. */
		if (ag != startag)
			continue;

		/* Allow sleeping in xfs_alloc_pagf_init() on the 2nd pass. */
		if (trylock != 0) {
			trylock = 0;
			continue;
		}

		/* Finally, if lowspace wasn't set, set it for the 3rd pass. */
		if (!(flags & XFS_PICK_LOWSPACE)) {
			flags |= XFS_PICK_LOWSPACE;
			continue;
		}

		/*
		 * Take the AG with the most free space, regardless of whether
		 * it's already in use by another filestream.
		 */
		if (max_ag != NULLAGNUMBER) {
			xfs_filestream_get_ag(mp, max_ag);
			free = maxfree;
			*agp = max_ag;
			break;
		}

		/* take AG 0 if none matched */
		trace_xfs_filestream_pick(ip, *agp, free, nscan);
		*agp = 0;
		return 0;
	}

	trace_xfs_filestream_pick(ip, *agp, free, nscan);

	if (*agp == NULLAGNUMBER)
		return 0;

	err = -ENOMEM;
	item = kmem_alloc(sizeof(*item), KM_MAYFAIL);
	if (!item)
		goto out_put_ag;

	item->ag = *agp;

	err = xfs_mru_cache_insert(mp->m_filestream, ip->i_ino, &item->mru);
	if (err) {
		if (err == -EEXIST)
			err = 0;
		goto out_free_item;
	}

	return 0;

out_free_item:
	kmem_free(item);
out_put_ag:
	xfs_filestream_put_ag(mp, *agp);
	return err;
}