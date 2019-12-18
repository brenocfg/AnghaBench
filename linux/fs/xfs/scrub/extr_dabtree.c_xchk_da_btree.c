#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_dablk_t ;
typedef  int (* xchk_da_btree_rec_fn ) (struct xchk_da_btree*,int,void*) ;
struct xfs_scrub {int /*<<< orphan*/  tp; TYPE_4__* sm; int /*<<< orphan*/  ip; struct xfs_mount* mp; } ;
struct xfs_mount {TYPE_1__* m_dir_geo; TYPE_1__* m_attr_geo; } ;
struct xfs_da_state_blk {scalar_t__ index; scalar_t__ magic; int /*<<< orphan*/ * bp; } ;
struct xfs_da_node_entry {int /*<<< orphan*/  before; int /*<<< orphan*/  hashval; } ;
struct TYPE_8__ {int whichfork; TYPE_1__* geo; int /*<<< orphan*/  op_flags; int /*<<< orphan*/  trans; int /*<<< orphan*/  dp; } ;
struct xchk_da_btree {scalar_t__* maxrecs; TYPE_5__* state; int /*<<< orphan*/  tree_level; scalar_t__ lowest; TYPE_2__ dargs; scalar_t__ highest; void* private; struct xfs_scrub* sc; } ;
struct TYPE_9__ {struct xfs_da_state_blk* blk; } ;
struct TYPE_11__ {TYPE_3__ path; struct xfs_mount* mp; TYPE_2__* args; } ;
struct TYPE_10__ {int sm_flags; } ;
struct TYPE_7__ {scalar_t__ freeblk; scalar_t__ leafblk; } ;

/* Variables and functions */
 int XFS_ATTR_FORK ; 
 scalar_t__ XFS_DA_NODE_MAGIC ; 
 int XFS_DA_NODE_MAXDEPTH ; 
 int /*<<< orphan*/  XFS_DA_OP_OKNOENT ; 
 scalar_t__ XFS_DINODE_FMT_BTREE ; 
 scalar_t__ XFS_DINODE_FMT_EXTENTS ; 
 scalar_t__ XFS_IFORK_FORMAT (int /*<<< orphan*/ ,int) ; 
 int XFS_SCRUB_OFLAG_CORRUPT ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int xchk_da_btree_block (struct xchk_da_btree*,int,scalar_t__) ; 
 void* xchk_da_btree_entry (struct xchk_da_btree*,int,scalar_t__) ; 
 int xchk_da_btree_hash (struct xchk_da_btree*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xchk_da_set_corrupt (struct xchk_da_btree*,int) ; 
 scalar_t__ xchk_should_terminate (struct xfs_scrub*,int*) ; 
 TYPE_5__* xfs_da_state_alloc () ; 
 int /*<<< orphan*/  xfs_da_state_free (TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
xchk_da_btree(
	struct xfs_scrub		*sc,
	int				whichfork,
	xchk_da_btree_rec_fn		scrub_fn,
	void				*private)
{
	struct xchk_da_btree		ds = {};
	struct xfs_mount		*mp = sc->mp;
	struct xfs_da_state_blk		*blks;
	struct xfs_da_node_entry	*key;
	void				*rec;
	xfs_dablk_t			blkno;
	int				level;
	int				error;

	/* Skip short format data structures; no btree to scan. */
	if (XFS_IFORK_FORMAT(sc->ip, whichfork) != XFS_DINODE_FMT_EXTENTS &&
	    XFS_IFORK_FORMAT(sc->ip, whichfork) != XFS_DINODE_FMT_BTREE)
		return 0;

	/* Set up initial da state. */
	ds.dargs.dp = sc->ip;
	ds.dargs.whichfork = whichfork;
	ds.dargs.trans = sc->tp;
	ds.dargs.op_flags = XFS_DA_OP_OKNOENT;
	ds.state = xfs_da_state_alloc();
	ds.state->args = &ds.dargs;
	ds.state->mp = mp;
	ds.sc = sc;
	ds.private = private;
	if (whichfork == XFS_ATTR_FORK) {
		ds.dargs.geo = mp->m_attr_geo;
		ds.lowest = 0;
		ds.highest = 0;
	} else {
		ds.dargs.geo = mp->m_dir_geo;
		ds.lowest = ds.dargs.geo->leafblk;
		ds.highest = ds.dargs.geo->freeblk;
	}
	blkno = ds.lowest;
	level = 0;

	/* Find the root of the da tree, if present. */
	blks = ds.state->path.blk;
	error = xchk_da_btree_block(&ds, level, blkno);
	if (error)
		goto out_state;
	/*
	 * We didn't find a block at ds.lowest, which means that there's
	 * no LEAF1/LEAFN tree (at least not where it's supposed to be),
	 * so jump out now.
	 */
	if (blks[level].bp == NULL)
		goto out_state;

	blks[level].index = 0;
	while (level >= 0 && level < XFS_DA_NODE_MAXDEPTH) {
		/* Handle leaf block. */
		if (blks[level].magic != XFS_DA_NODE_MAGIC) {
			/* End of leaf, pop back towards the root. */
			if (blks[level].index >= ds.maxrecs[level]) {
				if (level > 0)
					blks[level - 1].index++;
				ds.tree_level++;
				level--;
				continue;
			}

			/* Dispatch record scrubbing. */
			rec = xchk_da_btree_entry(&ds, level,
					blks[level].index);
			error = scrub_fn(&ds, level, rec);
			if (error)
				break;
			if (xchk_should_terminate(sc, &error) ||
			    (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT))
				break;

			blks[level].index++;
			continue;
		}


		/* End of node, pop back towards the root. */
		if (blks[level].index >= ds.maxrecs[level]) {
			if (level > 0)
				blks[level - 1].index++;
			ds.tree_level++;
			level--;
			continue;
		}

		/* Hashes in order for scrub? */
		key = xchk_da_btree_entry(&ds, level, blks[level].index);
		error = xchk_da_btree_hash(&ds, level, &key->hashval);
		if (error)
			goto out;

		/* Drill another level deeper. */
		blkno = be32_to_cpu(key->before);
		level++;
		if (level >= XFS_DA_NODE_MAXDEPTH) {
			/* Too deep! */
			xchk_da_set_corrupt(&ds, level - 1);
			break;
		}
		ds.tree_level--;
		error = xchk_da_btree_block(&ds, level, blkno);
		if (error)
			goto out;
		if (blks[level].bp == NULL)
			goto out;

		blks[level].index = 0;
	}

out:
	/* Release all the buffers we're tracking. */
	for (level = 0; level < XFS_DA_NODE_MAXDEPTH; level++) {
		if (blks[level].bp == NULL)
			continue;
		xfs_trans_brelse(sc->tp, blks[level].bp);
		blks[level].bp = NULL;
	}

out_state:
	xfs_da_state_free(ds.state);
	return error;
}