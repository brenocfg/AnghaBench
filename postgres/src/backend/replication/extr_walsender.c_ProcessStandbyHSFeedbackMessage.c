#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32 ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  replyTime; } ;
typedef  TYPE_1__ WalSnd ;
typedef  void* TransactionId ;
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_5__ {void* xmin; } ;

/* Variables and functions */
 scalar_t__ DEBUG2 ; 
 void* InvalidTransactionId ; 
 TYPE_3__* MyPgXact ; 
 int /*<<< orphan*/ * MyReplicationSlot ; 
 TYPE_1__* MyWalSnd ; 
 int /*<<< orphan*/  PhysicalReplicationSlotNewXmin (void*,void*) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TransactionIdInRecentPast (void*,void*) ; 
 scalar_t__ TransactionIdIsNormal (void*) ; 
 scalar_t__ TransactionIdPrecedes (void*,void*) ; 
 int /*<<< orphan*/  elog (scalar_t__,char*,void*,void*,void*,void*,char*) ; 
 scalar_t__ log_min_messages ; 
 int /*<<< orphan*/  pfree (char*) ; 
 void* pq_getmsgint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pq_getmsgint64 (int /*<<< orphan*/ *) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reply_message ; 
 int /*<<< orphan*/  timestamptz_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ProcessStandbyHSFeedbackMessage(void)
{
	TransactionId feedbackXmin;
	uint32		feedbackEpoch;
	TransactionId feedbackCatalogXmin;
	uint32		feedbackCatalogEpoch;
	TimestampTz replyTime;

	/*
	 * Decipher the reply message. The caller already consumed the msgtype
	 * byte. See XLogWalRcvSendHSFeedback() in walreceiver.c for the creation
	 * of this message.
	 */
	replyTime = pq_getmsgint64(&reply_message);
	feedbackXmin = pq_getmsgint(&reply_message, 4);
	feedbackEpoch = pq_getmsgint(&reply_message, 4);
	feedbackCatalogXmin = pq_getmsgint(&reply_message, 4);
	feedbackCatalogEpoch = pq_getmsgint(&reply_message, 4);

	if (log_min_messages <= DEBUG2)
	{
		char	   *replyTimeStr;

		/* Copy because timestamptz_to_str returns a static buffer */
		replyTimeStr = pstrdup(timestamptz_to_str(replyTime));

		elog(DEBUG2, "hot standby feedback xmin %u epoch %u, catalog_xmin %u epoch %u reply_time %s",
			 feedbackXmin,
			 feedbackEpoch,
			 feedbackCatalogXmin,
			 feedbackCatalogEpoch,
			 replyTimeStr);

		pfree(replyTimeStr);
	}

	/*
	 * Update shared state for this WalSender process based on reply data from
	 * standby.
	 */
	{
		WalSnd	   *walsnd = MyWalSnd;

		SpinLockAcquire(&walsnd->mutex);
		walsnd->replyTime = replyTime;
		SpinLockRelease(&walsnd->mutex);
	}

	/*
	 * Unset WalSender's xmins if the feedback message values are invalid.
	 * This happens when the downstream turned hot_standby_feedback off.
	 */
	if (!TransactionIdIsNormal(feedbackXmin)
		&& !TransactionIdIsNormal(feedbackCatalogXmin))
	{
		MyPgXact->xmin = InvalidTransactionId;
		if (MyReplicationSlot != NULL)
			PhysicalReplicationSlotNewXmin(feedbackXmin, feedbackCatalogXmin);
		return;
	}

	/*
	 * Check that the provided xmin/epoch are sane, that is, not in the future
	 * and not so far back as to be already wrapped around.  Ignore if not.
	 */
	if (TransactionIdIsNormal(feedbackXmin) &&
		!TransactionIdInRecentPast(feedbackXmin, feedbackEpoch))
		return;

	if (TransactionIdIsNormal(feedbackCatalogXmin) &&
		!TransactionIdInRecentPast(feedbackCatalogXmin, feedbackCatalogEpoch))
		return;

	/*
	 * Set the WalSender's xmin equal to the standby's requested xmin, so that
	 * the xmin will be taken into account by GetOldestXmin.  This will hold
	 * back the removal of dead rows and thereby prevent the generation of
	 * cleanup conflicts on the standby server.
	 *
	 * There is a small window for a race condition here: although we just
	 * checked that feedbackXmin precedes nextXid, the nextXid could have
	 * gotten advanced between our fetching it and applying the xmin below,
	 * perhaps far enough to make feedbackXmin wrap around.  In that case the
	 * xmin we set here would be "in the future" and have no effect.  No point
	 * in worrying about this since it's too late to save the desired data
	 * anyway.  Assuming that the standby sends us an increasing sequence of
	 * xmins, this could only happen during the first reply cycle, else our
	 * own xmin would prevent nextXid from advancing so far.
	 *
	 * We don't bother taking the ProcArrayLock here.  Setting the xmin field
	 * is assumed atomic, and there's no real need to prevent a concurrent
	 * GetOldestXmin.  (If we're moving our xmin forward, this is obviously
	 * safe, and if we're moving it backwards, well, the data is at risk
	 * already since a VACUUM could have just finished calling GetOldestXmin.)
	 *
	 * If we're using a replication slot we reserve the xmin via that,
	 * otherwise via the walsender's PGXACT entry. We can only track the
	 * catalog xmin separately when using a slot, so we store the least of the
	 * two provided when not using a slot.
	 *
	 * XXX: It might make sense to generalize the ephemeral slot concept and
	 * always use the slot mechanism to handle the feedback xmin.
	 */
	if (MyReplicationSlot != NULL)	/* XXX: persistency configurable? */
		PhysicalReplicationSlotNewXmin(feedbackXmin, feedbackCatalogXmin);
	else
	{
		if (TransactionIdIsNormal(feedbackCatalogXmin)
			&& TransactionIdPrecedes(feedbackCatalogXmin, feedbackXmin))
			MyPgXact->xmin = feedbackCatalogXmin;
		else
			MyPgXact->xmin = feedbackXmin;
	}
}