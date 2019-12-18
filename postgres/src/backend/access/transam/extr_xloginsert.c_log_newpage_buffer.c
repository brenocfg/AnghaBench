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
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  ForkNumber ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetTag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CritSectionCount ; 
 int /*<<< orphan*/  log_newpage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

XLogRecPtr
log_newpage_buffer(Buffer buffer, bool page_std)
{
	Page		page = BufferGetPage(buffer);
	RelFileNode rnode;
	ForkNumber	forkNum;
	BlockNumber blkno;

	/* Shared buffers should be modified in a critical section. */
	Assert(CritSectionCount > 0);

	BufferGetTag(buffer, &rnode, &forkNum, &blkno);

	return log_newpage(&rnode, forkNum, blkno, page, page_std);
}