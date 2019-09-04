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
struct TYPE_2__ {scalar_t__* stree; } ;
struct dmap {TYPE_1__ tree; } ;
struct bmap {int dummy; } ;
typedef  scalar_t__ s8 ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  dmtree_t ;

/* Variables and functions */
 int BPERDMAP ; 
 int L2DBWORD ; 
 scalar_t__ NOFREE ; 
 size_t ROOT ; 
 int dbAdjCtl (struct bmap*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbAllocBits (struct bmap*,struct dmap*,int,int) ; 
 int /*<<< orphan*/  dbBackSplit (int /*<<< orphan*/ *,int) ; 
 int dbFreeBits (struct bmap*,struct dmap*,int,int) ; 

__attribute__((used)) static int dbFreeDmap(struct bmap * bmp, struct dmap * dp, s64 blkno,
		      int nblocks)
{
	s8 oldroot;
	int rc = 0, word;

	/* save the current value of the root (i.e. maximum free string)
	 * of the dmap tree.
	 */
	oldroot = dp->tree.stree[ROOT];

	/* free the specified (blocks) bits */
	rc = dbFreeBits(bmp, dp, blkno, nblocks);

	/* if error or the root has not changed, done. */
	if (rc || (dp->tree.stree[ROOT] == oldroot))
		return (rc);

	/* root changed. bubble the change up to the dmap control pages.
	 * if the adjustment of the upper level control pages fails,
	 * backout the deallocation.
	 */
	if ((rc = dbAdjCtl(bmp, blkno, dp->tree.stree[ROOT], 0, 0))) {
		word = (blkno & (BPERDMAP - 1)) >> L2DBWORD;

		/* as part of backing out the deallocation, we will have
		 * to back split the dmap tree if the deallocation caused
		 * the freed blocks to become part of a larger binary buddy
		 * system.
		 */
		if (dp->tree.stree[word] == NOFREE)
			dbBackSplit((dmtree_t *) & dp->tree, word);

		dbAllocBits(bmp, dp, blkno, nblocks);
	}

	return (rc);
}