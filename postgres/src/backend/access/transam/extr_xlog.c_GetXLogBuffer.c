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
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  scalar_t__ XLogRecPtr ;
typedef  TYPE_1__* XLogPageHeader ;
struct TYPE_4__ {scalar_t__* xlblocks; char* pages; } ;
struct TYPE_3__ {scalar_t__ xlp_magic; scalar_t__ xlp_pageaddr; } ;
typedef  int Size ;

/* Variables and functions */
 int /*<<< orphan*/  AdvanceXLInsertBuffer (scalar_t__,int) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  PANIC ; 
 scalar_t__ SizeOfXLogLongPHD ; 
 scalar_t__ SizeOfXLogShortPHD ; 
 int /*<<< orphan*/  WALInsertLockUpdateInsertingAt (scalar_t__) ; 
 scalar_t__ XLOG_BLCKSZ ; 
 scalar_t__ XLOG_PAGE_MAGIC ; 
 TYPE_2__* XLogCtl ; 
 int XLogRecPtrToBufIdx (scalar_t__) ; 
 scalar_t__ XLogSegmentOffset (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_memory_barrier () ; 
 int /*<<< orphan*/  wal_segment_size ; 

__attribute__((used)) static char *
GetXLogBuffer(XLogRecPtr ptr)
{
	int			idx;
	XLogRecPtr	endptr;
	static uint64 cachedPage = 0;
	static char *cachedPos = NULL;
	XLogRecPtr	expectedEndPtr;

	/*
	 * Fast path for the common case that we need to access again the same
	 * page as last time.
	 */
	if (ptr / XLOG_BLCKSZ == cachedPage)
	{
		Assert(((XLogPageHeader) cachedPos)->xlp_magic == XLOG_PAGE_MAGIC);
		Assert(((XLogPageHeader) cachedPos)->xlp_pageaddr == ptr - (ptr % XLOG_BLCKSZ));
		return cachedPos + ptr % XLOG_BLCKSZ;
	}

	/*
	 * The XLog buffer cache is organized so that a page is always loaded to a
	 * particular buffer.  That way we can easily calculate the buffer a given
	 * page must be loaded into, from the XLogRecPtr alone.
	 */
	idx = XLogRecPtrToBufIdx(ptr);

	/*
	 * See what page is loaded in the buffer at the moment. It could be the
	 * page we're looking for, or something older. It can't be anything newer
	 * - that would imply the page we're looking for has already been written
	 * out to disk and evicted, and the caller is responsible for making sure
	 * that doesn't happen.
	 *
	 * However, we don't hold a lock while we read the value. If someone has
	 * just initialized the page, it's possible that we get a "torn read" of
	 * the XLogRecPtr if 64-bit fetches are not atomic on this platform. In
	 * that case we will see a bogus value. That's ok, we'll grab the mapping
	 * lock (in AdvanceXLInsertBuffer) and retry if we see anything else than
	 * the page we're looking for. But it means that when we do this unlocked
	 * read, we might see a value that appears to be ahead of the page we're
	 * looking for. Don't PANIC on that, until we've verified the value while
	 * holding the lock.
	 */
	expectedEndPtr = ptr;
	expectedEndPtr += XLOG_BLCKSZ - ptr % XLOG_BLCKSZ;

	endptr = XLogCtl->xlblocks[idx];
	if (expectedEndPtr != endptr)
	{
		XLogRecPtr	initializedUpto;

		/*
		 * Before calling AdvanceXLInsertBuffer(), which can block, let others
		 * know how far we're finished with inserting the record.
		 *
		 * NB: If 'ptr' points to just after the page header, advertise a
		 * position at the beginning of the page rather than 'ptr' itself. If
		 * there are no other insertions running, someone might try to flush
		 * up to our advertised location. If we advertised a position after
		 * the page header, someone might try to flush the page header, even
		 * though page might actually not be initialized yet. As the first
		 * inserter on the page, we are effectively responsible for making
		 * sure that it's initialized, before we let insertingAt to move past
		 * the page header.
		 */
		if (ptr % XLOG_BLCKSZ == SizeOfXLogShortPHD &&
			XLogSegmentOffset(ptr, wal_segment_size) > XLOG_BLCKSZ)
			initializedUpto = ptr - SizeOfXLogShortPHD;
		else if (ptr % XLOG_BLCKSZ == SizeOfXLogLongPHD &&
				 XLogSegmentOffset(ptr, wal_segment_size) < XLOG_BLCKSZ)
			initializedUpto = ptr - SizeOfXLogLongPHD;
		else
			initializedUpto = ptr;

		WALInsertLockUpdateInsertingAt(initializedUpto);

		AdvanceXLInsertBuffer(ptr, false);
		endptr = XLogCtl->xlblocks[idx];

		if (expectedEndPtr != endptr)
			elog(PANIC, "could not find WAL buffer for %X/%X",
				 (uint32) (ptr >> 32), (uint32) ptr);
	}
	else
	{
		/*
		 * Make sure the initialization of the page is visible to us, and
		 * won't arrive later to overwrite the WAL data we write on the page.
		 */
		pg_memory_barrier();
	}

	/*
	 * Found the buffer holding this page. Return a pointer to the right
	 * offset within the page.
	 */
	cachedPage = ptr / XLOG_BLCKSZ;
	cachedPos = XLogCtl->pages + idx * (Size) XLOG_BLCKSZ;

	Assert(((XLogPageHeader) cachedPos)->xlp_magic == XLOG_PAGE_MAGIC);
	Assert(((XLogPageHeader) cachedPos)->xlp_pageaddr == ptr - (ptr % XLOG_BLCKSZ));

	return cachedPos + ptr % XLOG_BLCKSZ;
}