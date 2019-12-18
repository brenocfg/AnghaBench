#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8 ;
typedef  int uint16 ;
struct TYPE_5__ {scalar_t__* fp_nodes; int fp_next_slot; } ;
struct TYPE_4__ {int /*<<< orphan*/  relNode; int /*<<< orphan*/  dbNode; int /*<<< orphan*/  spcNode; } ;
typedef  TYPE_1__ RelFileNode ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  ForkNumber ;
typedef  TYPE_2__* FSMPage ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetTag (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int LeafNodesPerPage ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirtyHint (int /*<<< orphan*/ ,int) ; 
 int NodesPerPage ; 
 int NonLeafNodesPerPage ; 
 int /*<<< orphan*/  PageGetContents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm_rebuild_page (int /*<<< orphan*/ ) ; 
 int leftchild (int) ; 
 int parentof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rightneighbor (int) ; 

int
fsm_search_avail(Buffer buf, uint8 minvalue, bool advancenext,
				 bool exclusive_lock_held)
{
	Page		page = BufferGetPage(buf);
	FSMPage		fsmpage = (FSMPage) PageGetContents(page);
	int			nodeno;
	int			target;
	uint16		slot;

restart:

	/*
	 * Check the root first, and exit quickly if there's no leaf with enough
	 * free space
	 */
	if (fsmpage->fp_nodes[0] < minvalue)
		return -1;

	/*
	 * Start search using fp_next_slot.  It's just a hint, so check that it's
	 * sane.  (This also handles wrapping around when the prior call returned
	 * the last slot on the page.)
	 */
	target = fsmpage->fp_next_slot;
	if (target < 0 || target >= LeafNodesPerPage)
		target = 0;
	target += NonLeafNodesPerPage;

	/*----------
	 * Start the search from the target slot.  At every step, move one
	 * node to the right, then climb up to the parent.  Stop when we reach
	 * a node with enough free space (as we must, since the root has enough
	 * space).
	 *
	 * The idea is to gradually expand our "search triangle", that is, all
	 * nodes covered by the current node, and to be sure we search to the
	 * right from the start point.  At the first step, only the target slot
	 * is examined.  When we move up from a left child to its parent, we are
	 * adding the right-hand subtree of that parent to the search triangle.
	 * When we move right then up from a right child, we are dropping the
	 * current search triangle (which we know doesn't contain any suitable
	 * page) and instead looking at the next-larger-size triangle to its
	 * right.  So we never look left from our original start point, and at
	 * each step the size of the search triangle doubles, ensuring it takes
	 * only log2(N) work to search N pages.
	 *
	 * The "move right" operation will wrap around if it hits the right edge
	 * of the tree, so the behavior is still good if we start near the right.
	 * Note also that the move-and-climb behavior ensures that we can't end
	 * up on one of the missing nodes at the right of the leaf level.
	 *
	 * For example, consider this tree:
	 *
	 *		   7
	 *	   7	   6
	 *	 5	 7	 6	 5
	 *	4 5 5 7 2 6 5 2
	 *				T
	 *
	 * Assume that the target node is the node indicated by the letter T,
	 * and we're searching for a node with value of 6 or higher. The search
	 * begins at T. At the first iteration, we move to the right, then to the
	 * parent, arriving at the rightmost 5. At the second iteration, we move
	 * to the right, wrapping around, then climb up, arriving at the 7 on the
	 * third level.  7 satisfies our search, so we descend down to the bottom,
	 * following the path of sevens.  This is in fact the first suitable page
	 * to the right of (allowing for wraparound) our start point.
	 *----------
	 */
	nodeno = target;
	while (nodeno > 0)
	{
		if (fsmpage->fp_nodes[nodeno] >= minvalue)
			break;

		/*
		 * Move to the right, wrapping around on same level if necessary, then
		 * climb up.
		 */
		nodeno = parentof(rightneighbor(nodeno));
	}

	/*
	 * We're now at a node with enough free space, somewhere in the middle of
	 * the tree. Descend to the bottom, following a path with enough free
	 * space, preferring to move left if there's a choice.
	 */
	while (nodeno < NonLeafNodesPerPage)
	{
		int			childnodeno = leftchild(nodeno);

		if (childnodeno < NodesPerPage &&
			fsmpage->fp_nodes[childnodeno] >= minvalue)
		{
			nodeno = childnodeno;
			continue;
		}
		childnodeno++;			/* point to right child */
		if (childnodeno < NodesPerPage &&
			fsmpage->fp_nodes[childnodeno] >= minvalue)
		{
			nodeno = childnodeno;
		}
		else
		{
			/*
			 * Oops. The parent node promised that either left or right child
			 * has enough space, but neither actually did. This can happen in
			 * case of a "torn page", IOW if we crashed earlier while writing
			 * the page to disk, and only part of the page made it to disk.
			 *
			 * Fix the corruption and restart.
			 */
			RelFileNode rnode;
			ForkNumber	forknum;
			BlockNumber blknum;

			BufferGetTag(buf, &rnode, &forknum, &blknum);
			elog(DEBUG1, "fixing corrupt FSM block %u, relation %u/%u/%u",
				 blknum, rnode.spcNode, rnode.dbNode, rnode.relNode);

			/* make sure we hold an exclusive lock */
			if (!exclusive_lock_held)
			{
				LockBuffer(buf, BUFFER_LOCK_UNLOCK);
				LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);
				exclusive_lock_held = true;
			}
			fsm_rebuild_page(page);
			MarkBufferDirtyHint(buf, false);
			goto restart;
		}
	}

	/* We're now at the bottom level, at a node with enough space. */
	slot = nodeno - NonLeafNodesPerPage;

	/*
	 * Update the next-target pointer. Note that we do this even if we're only
	 * holding a shared lock, on the grounds that it's better to use a shared
	 * lock and get a garbled next pointer every now and then, than take the
	 * concurrency hit of an exclusive lock.
	 *
	 * Wrap-around is handled at the beginning of this function.
	 */
	fsmpage->fp_next_slot = slot + (advancenext ? 1 : 0);

	return slot;
}