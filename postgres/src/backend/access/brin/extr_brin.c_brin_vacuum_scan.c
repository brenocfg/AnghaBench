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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  BufferAccessStrategy ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  FreeSpaceMapVacuum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brin_page_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
brin_vacuum_scan(Relation idxrel, BufferAccessStrategy strategy)
{
	BlockNumber nblocks;
	BlockNumber blkno;

	/*
	 * Scan the index in physical order, and clean up any possible mess in
	 * each page.
	 */
	nblocks = RelationGetNumberOfBlocks(idxrel);
	for (blkno = 0; blkno < nblocks; blkno++)
	{
		Buffer		buf;

		CHECK_FOR_INTERRUPTS();

		buf = ReadBufferExtended(idxrel, MAIN_FORKNUM, blkno,
								 RBM_NORMAL, strategy);

		brin_page_cleanup(idxrel, buf);

		ReleaseBuffer(buf);
	}

	/*
	 * Update all upper pages in the index's FSM, as well.  This ensures not
	 * only that we propagate leaf-page FSM updates made by brin_page_cleanup,
	 * but also that any pre-existing damage or out-of-dateness is repaired.
	 */
	FreeSpaceMapVacuum(idxrel);
}