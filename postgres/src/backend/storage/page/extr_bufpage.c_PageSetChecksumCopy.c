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
struct TYPE_2__ {int /*<<< orphan*/  pd_checksum; } ;
typedef  TYPE_1__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BLCKSZ ; 
 int /*<<< orphan*/  DataChecksumsEnabled () ; 
 char* MemoryContextAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PageIsNew (scalar_t__) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_checksum_page (char*,int /*<<< orphan*/ ) ; 

char *
PageSetChecksumCopy(Page page, BlockNumber blkno)
{
	static char *pageCopy = NULL;

	/* If we don't need a checksum, just return the passed-in data */
	if (PageIsNew(page) || !DataChecksumsEnabled())
		return (char *) page;

	/*
	 * We allocate the copy space once and use it over on each subsequent
	 * call.  The point of palloc'ing here, rather than having a static char
	 * array, is first to ensure adequate alignment for the checksumming code
	 * and second to avoid wasting space in processes that never call this.
	 */
	if (pageCopy == NULL)
		pageCopy = MemoryContextAlloc(TopMemoryContext, BLCKSZ);

	memcpy(pageCopy, (char *) page, BLCKSZ);
	((PageHeader) pageCopy)->pd_checksum = pg_checksum_page(pageCopy, blkno);
	return pageCopy;
}