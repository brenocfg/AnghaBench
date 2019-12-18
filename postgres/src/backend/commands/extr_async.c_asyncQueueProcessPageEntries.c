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
struct TYPE_2__ {scalar_t__ dboid; char* data; int /*<<< orphan*/  srcPid; int /*<<< orphan*/  xid; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  volatile QueuePosition ;
typedef  TYPE_1__ AsyncQueueEntry ;

/* Variables and functions */
 scalar_t__ IsListeningOn (char*) ; 
 scalar_t__ MyDatabaseId ; 
 int /*<<< orphan*/  NotifyMyFrontEnd (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ QUEUE_POS_EQUAL (int /*<<< orphan*/  volatile,int /*<<< orphan*/  volatile) ; 
 int QUEUE_POS_OFFSET (int /*<<< orphan*/  volatile) ; 
 scalar_t__ TransactionIdDidCommit (int /*<<< orphan*/ ) ; 
 scalar_t__ XidInMVCCSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int asyncQueueAdvance (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static bool
asyncQueueProcessPageEntries(volatile QueuePosition *current,
							 QueuePosition stop,
							 char *page_buffer,
							 Snapshot snapshot)
{
	bool		reachedStop = false;
	bool		reachedEndOfPage;
	AsyncQueueEntry *qe;

	do
	{
		QueuePosition thisentry = *current;

		if (QUEUE_POS_EQUAL(thisentry, stop))
			break;

		qe = (AsyncQueueEntry *) (page_buffer + QUEUE_POS_OFFSET(thisentry));

		/*
		 * Advance *current over this message, possibly to the next page. As
		 * noted in the comments for asyncQueueReadAllNotifications, we must
		 * do this before possibly failing while processing the message.
		 */
		reachedEndOfPage = asyncQueueAdvance(current, qe->length);

		/* Ignore messages destined for other databases */
		if (qe->dboid == MyDatabaseId)
		{
			if (XidInMVCCSnapshot(qe->xid, snapshot))
			{
				/*
				 * The source transaction is still in progress, so we can't
				 * process this message yet.  Break out of the loop, but first
				 * back up *current so we will reprocess the message next
				 * time.  (Note: it is unlikely but not impossible for
				 * TransactionIdDidCommit to fail, so we can't really avoid
				 * this advance-then-back-up behavior when dealing with an
				 * uncommitted message.)
				 *
				 * Note that we must test XidInMVCCSnapshot before we test
				 * TransactionIdDidCommit, else we might return a message from
				 * a transaction that is not yet visible to snapshots; compare
				 * the comments at the head of heapam_visibility.c.
				 *
				 * Also, while our own xact won't be listed in the snapshot,
				 * we need not check for TransactionIdIsCurrentTransactionId
				 * because our transaction cannot (yet) have queued any
				 * messages.
				 */
				*current = thisentry;
				reachedStop = true;
				break;
			}
			else if (TransactionIdDidCommit(qe->xid))
			{
				/* qe->data is the null-terminated channel name */
				char	   *channel = qe->data;

				if (IsListeningOn(channel))
				{
					/* payload follows channel name */
					char	   *payload = qe->data + strlen(channel) + 1;

					NotifyMyFrontEnd(channel, payload, qe->srcPid);
				}
			}
			else
			{
				/*
				 * The source transaction aborted or crashed, so we just
				 * ignore its notifications.
				 */
			}
		}

		/* Loop back if we're not at end of page */
	} while (!reachedEndOfPage);

	if (QUEUE_POS_EQUAL(*current, stop))
		reachedStop = true;

	return reachedStop;
}