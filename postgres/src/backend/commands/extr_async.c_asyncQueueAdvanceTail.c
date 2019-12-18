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
typedef  int /*<<< orphan*/  QueuePosition ;
typedef  scalar_t__ BackendId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AsyncCtl ; 
 int /*<<< orphan*/  AsyncQueueLock ; 
 scalar_t__ InvalidPid ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 scalar_t__ QUEUE_BACKEND_PID (scalar_t__) ; 
 int /*<<< orphan*/  QUEUE_BACKEND_POS (scalar_t__) ; 
 scalar_t__ QUEUE_FIRST_LISTENER ; 
 int /*<<< orphan*/  QUEUE_HEAD ; 
 scalar_t__ QUEUE_NEXT_LISTENER (scalar_t__) ; 
 int /*<<< orphan*/  QUEUE_POS_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int QUEUE_POS_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUEUE_TAIL ; 
 int SLRU_PAGES_PER_SEGMENT ; 
 int /*<<< orphan*/  SimpleLruTruncate (int /*<<< orphan*/ ,int) ; 
 scalar_t__ asyncQueuePagePrecedes (int,int) ; 

__attribute__((used)) static void
asyncQueueAdvanceTail(void)
{
	QueuePosition min;
	int			oldtailpage;
	int			newtailpage;
	int			boundary;

	LWLockAcquire(AsyncQueueLock, LW_EXCLUSIVE);
	min = QUEUE_HEAD;
	for (BackendId i = QUEUE_FIRST_LISTENER; i > 0; i = QUEUE_NEXT_LISTENER(i))
	{
		Assert(QUEUE_BACKEND_PID(i) != InvalidPid);
		min = QUEUE_POS_MIN(min, QUEUE_BACKEND_POS(i));
	}
	oldtailpage = QUEUE_POS_PAGE(QUEUE_TAIL);
	QUEUE_TAIL = min;
	LWLockRelease(AsyncQueueLock);

	/*
	 * We can truncate something if the global tail advanced across an SLRU
	 * segment boundary.
	 *
	 * XXX it might be better to truncate only once every several segments, to
	 * reduce the number of directory scans.
	 */
	newtailpage = QUEUE_POS_PAGE(min);
	boundary = newtailpage - (newtailpage % SLRU_PAGES_PER_SEGMENT);
	if (asyncQueuePagePrecedes(oldtailpage, boundary))
	{
		/*
		 * SimpleLruTruncate() will ask for AsyncCtlLock but will also release
		 * the lock again.
		 */
		SimpleLruTruncate(AsyncCtl, newtailpage);
	}
}