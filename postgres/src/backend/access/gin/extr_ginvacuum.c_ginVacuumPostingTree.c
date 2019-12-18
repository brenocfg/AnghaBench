#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int isRoot; struct TYPE_10__* child; int /*<<< orphan*/  leftBlkno; } ;
struct TYPE_9__ {int /*<<< orphan*/  strategy; int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ GinVacuumState ;
typedef  TYPE_2__ DataPageDeleteStack ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidBlockNumber ; 
 int /*<<< orphan*/  InvalidOffsetNumber ; 
 int /*<<< orphan*/  LockBufferForCleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ginScanToDelete (TYPE_1__*,int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ginVacuumPostingTreeLeaves (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

__attribute__((used)) static void
ginVacuumPostingTree(GinVacuumState *gvs, BlockNumber rootBlkno)
{
	if (ginVacuumPostingTreeLeaves(gvs, rootBlkno))
	{
		/*
		 * There is at least one empty page.  So we have to rescan the tree
		 * deleting empty pages.
		 */
		Buffer		buffer;
		DataPageDeleteStack root,
				   *ptr,
				   *tmp;

		buffer = ReadBufferExtended(gvs->index, MAIN_FORKNUM, rootBlkno,
									RBM_NORMAL, gvs->strategy);

		/*
		 * Lock posting tree root for cleanup to ensure there are no
		 * concurrent inserts.
		 */
		LockBufferForCleanup(buffer);

		memset(&root, 0, sizeof(DataPageDeleteStack));
		root.leftBlkno = InvalidBlockNumber;
		root.isRoot = true;

		ginScanToDelete(gvs, rootBlkno, true, &root, InvalidOffsetNumber);

		ptr = root.child;

		while (ptr)
		{
			tmp = ptr->child;
			pfree(ptr);
			ptr = tmp;
		}

		UnlockReleaseBuffer(buffer);
	}
}