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
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  GenericXLogState ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLOOM_METAPAGE_BLKNO ; 
 int /*<<< orphan*/  BloomFillMetapage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BloomNewBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC_XLOG_FULL_IMAGE ; 
 int /*<<< orphan*/  GenericXLogFinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GenericXLogRegisterBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GenericXLogStart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 

void
BloomInitMetapage(Relation index)
{
	Buffer		metaBuffer;
	Page		metaPage;
	GenericXLogState *state;

	/*
	 * Make a new page; since it is first page it should be associated with
	 * block number 0 (BLOOM_METAPAGE_BLKNO).
	 */
	metaBuffer = BloomNewBuffer(index);
	Assert(BufferGetBlockNumber(metaBuffer) == BLOOM_METAPAGE_BLKNO);

	/* Initialize contents of meta page */
	state = GenericXLogStart(index);
	metaPage = GenericXLogRegisterBuffer(state, metaBuffer,
										 GENERIC_XLOG_FULL_IMAGE);
	BloomFillMetapage(index, metaPage);
	GenericXLogFinish(state);

	UnlockReleaseBuffer(metaBuffer);
}