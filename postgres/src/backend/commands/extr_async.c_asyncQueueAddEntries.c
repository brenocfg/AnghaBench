#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* shared; } ;
struct TYPE_11__ {int /*<<< orphan*/  events; } ;
struct TYPE_10__ {scalar_t__ length; char* data; int /*<<< orphan*/  dboid; } ;
struct TYPE_9__ {int* page_dirty; scalar_t__* page_buffer; } ;
typedef  int /*<<< orphan*/  QueuePosition ;
typedef  int /*<<< orphan*/  Notification ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  TYPE_2__ AsyncQueueEntry ;

/* Variables and functions */
 TYPE_6__* AsyncCtl ; 
 int /*<<< orphan*/  AsyncCtlLock ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int QUEUE_CLEANUP_DELAY ; 
 int /*<<< orphan*/  QUEUE_HEAD ; 
 scalar_t__ QUEUE_PAGESIZE ; 
 int QUEUE_POS_OFFSET (int /*<<< orphan*/ ) ; 
 int QUEUE_POS_PAGE (int /*<<< orphan*/ ) ; 
 int SimpleLruReadPage (TYPE_6__*,int,int,int /*<<< orphan*/ ) ; 
 int SimpleLruZeroPage (TYPE_6__*,int) ; 
 scalar_t__ asyncQueueAdvance (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  asyncQueueNotificationToEntry (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int backendTryAdvanceTail ; 
 scalar_t__ lfirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lnext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,TYPE_2__*,scalar_t__) ; 
 TYPE_3__* pendingNotifies ; 

__attribute__((used)) static ListCell *
asyncQueueAddEntries(ListCell *nextNotify)
{
	AsyncQueueEntry qe;
	QueuePosition queue_head;
	int			pageno;
	int			offset;
	int			slotno;

	/* We hold both AsyncQueueLock and AsyncCtlLock during this operation */
	LWLockAcquire(AsyncCtlLock, LW_EXCLUSIVE);

	/*
	 * We work with a local copy of QUEUE_HEAD, which we write back to shared
	 * memory upon exiting.  The reason for this is that if we have to advance
	 * to a new page, SimpleLruZeroPage might fail (out of disk space, for
	 * instance), and we must not advance QUEUE_HEAD if it does.  (Otherwise,
	 * subsequent insertions would try to put entries into a page that slru.c
	 * thinks doesn't exist yet.)  So, use a local position variable.  Note
	 * that if we do fail, any already-inserted queue entries are forgotten;
	 * this is okay, since they'd be useless anyway after our transaction
	 * rolls back.
	 */
	queue_head = QUEUE_HEAD;

	/* Fetch the current page */
	pageno = QUEUE_POS_PAGE(queue_head);
	slotno = SimpleLruReadPage(AsyncCtl, pageno, true, InvalidTransactionId);
	/* Note we mark the page dirty before writing in it */
	AsyncCtl->shared->page_dirty[slotno] = true;

	while (nextNotify != NULL)
	{
		Notification *n = (Notification *) lfirst(nextNotify);

		/* Construct a valid queue entry in local variable qe */
		asyncQueueNotificationToEntry(n, &qe);

		offset = QUEUE_POS_OFFSET(queue_head);

		/* Check whether the entry really fits on the current page */
		if (offset + qe.length <= QUEUE_PAGESIZE)
		{
			/* OK, so advance nextNotify past this item */
			nextNotify = lnext(pendingNotifies->events, nextNotify);
		}
		else
		{
			/*
			 * Write a dummy entry to fill up the page. Actually readers will
			 * only check dboid and since it won't match any reader's database
			 * OID, they will ignore this entry and move on.
			 */
			qe.length = QUEUE_PAGESIZE - offset;
			qe.dboid = InvalidOid;
			qe.data[0] = '\0';	/* empty channel */
			qe.data[1] = '\0';	/* empty payload */
		}

		/* Now copy qe into the shared buffer page */
		memcpy(AsyncCtl->shared->page_buffer[slotno] + offset,
			   &qe,
			   qe.length);

		/* Advance queue_head appropriately, and detect if page is full */
		if (asyncQueueAdvance(&(queue_head), qe.length))
		{
			/*
			 * Page is full, so we're done here, but first fill the next page
			 * with zeroes.  The reason to do this is to ensure that slru.c's
			 * idea of the head page is always the same as ours, which avoids
			 * boundary problems in SimpleLruTruncate.  The test in
			 * asyncQueueIsFull() ensured that there is room to create this
			 * page without overrunning the queue.
			 */
			slotno = SimpleLruZeroPage(AsyncCtl, QUEUE_POS_PAGE(queue_head));

			/*
			 * If the new page address is a multiple of QUEUE_CLEANUP_DELAY,
			 * set flag to remember that we should try to advance the tail
			 * pointer (we don't want to actually do that right here).
			 */
			if (QUEUE_POS_PAGE(queue_head) % QUEUE_CLEANUP_DELAY == 0)
				backendTryAdvanceTail = true;

			/* And exit the loop */
			break;
		}
	}

	/* Success, so update the global QUEUE_HEAD */
	QUEUE_HEAD = queue_head;

	LWLockRelease(AsyncCtlLock);

	return nextNotify;
}