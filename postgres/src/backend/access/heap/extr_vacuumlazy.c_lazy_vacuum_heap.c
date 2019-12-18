#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_dead_tuples; int /*<<< orphan*/ * dead_tuples; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  PGRUsage ;
typedef  TYPE_1__ LVRelStats ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConditionalLockBufferForCleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  PageGetHeapFreeSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RecordPageWithFreeSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elevel ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_internal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int,int) ; 
 int lazy_vacuum_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_rusage_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_rusage_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vac_strategy ; 
 int /*<<< orphan*/  vacuum_delay_point () ; 

__attribute__((used)) static void
lazy_vacuum_heap(Relation onerel, LVRelStats *vacrelstats)
{
	int			tupindex;
	int			npages;
	PGRUsage	ru0;
	Buffer		vmbuffer = InvalidBuffer;

	pg_rusage_init(&ru0);
	npages = 0;

	tupindex = 0;
	while (tupindex < vacrelstats->num_dead_tuples)
	{
		BlockNumber tblk;
		Buffer		buf;
		Page		page;
		Size		freespace;

		vacuum_delay_point();

		tblk = ItemPointerGetBlockNumber(&vacrelstats->dead_tuples[tupindex]);
		buf = ReadBufferExtended(onerel, MAIN_FORKNUM, tblk, RBM_NORMAL,
								 vac_strategy);
		if (!ConditionalLockBufferForCleanup(buf))
		{
			ReleaseBuffer(buf);
			++tupindex;
			continue;
		}
		tupindex = lazy_vacuum_page(onerel, tblk, buf, tupindex, vacrelstats,
									&vmbuffer);

		/* Now that we've compacted the page, record its available space */
		page = BufferGetPage(buf);
		freespace = PageGetHeapFreeSpace(page);

		UnlockReleaseBuffer(buf);
		RecordPageWithFreeSpace(onerel, tblk, freespace);
		npages++;
	}

	if (BufferIsValid(vmbuffer))
	{
		ReleaseBuffer(vmbuffer);
		vmbuffer = InvalidBuffer;
	}

	ereport(elevel,
			(errmsg("\"%s\": removed %d row versions in %d pages",
					RelationGetRelationName(onerel),
					tupindex, npages),
			 errdetail_internal("%s", pg_rusage_show(&ru0))));
}