#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ TimestampTz ;
struct TYPE_6__ {scalar_t__ clock_time; scalar_t__ cutoff_time; int /*<<< orphan*/  databaseid; } ;
struct TYPE_5__ {scalar_t__ stats_timestamp; int /*<<< orphan*/  databaseid; } ;
typedef  TYPE_1__ PgStat_StatDBEntry ;
typedef  TYPE_2__ PgStat_MsgInquiry ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 ; 
 scalar_t__ GetCurrentTimestamp () ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  lappend_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_member_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pending_write_requests ; 
 int /*<<< orphan*/  pfree (char*) ; 
 TYPE_1__* pgstat_get_db_entry (int /*<<< orphan*/ ,int) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timestamptz_to_str (scalar_t__) ; 

__attribute__((used)) static void
pgstat_recv_inquiry(PgStat_MsgInquiry *msg, int len)
{
	PgStat_StatDBEntry *dbentry;

	elog(DEBUG2, "received inquiry for database %u", msg->databaseid);

	/*
	 * If there's already a write request for this DB, there's nothing to do.
	 *
	 * Note that if a request is found, we return early and skip the below
	 * check for clock skew.  This is okay, since the only way for a DB
	 * request to be present in the list is that we have been here since the
	 * last write round.  It seems sufficient to check for clock skew once per
	 * write round.
	 */
	if (list_member_oid(pending_write_requests, msg->databaseid))
		return;

	/*
	 * Check to see if we last wrote this database at a time >= the requested
	 * cutoff time.  If so, this is a stale request that was generated before
	 * we updated the DB file, and we don't need to do so again.
	 *
	 * If the requestor's local clock time is older than stats_timestamp, we
	 * should suspect a clock glitch, ie system time going backwards; though
	 * the more likely explanation is just delayed message receipt.  It is
	 * worth expending a GetCurrentTimestamp call to be sure, since a large
	 * retreat in the system clock reading could otherwise cause us to neglect
	 * to update the stats file for a long time.
	 */
	dbentry = pgstat_get_db_entry(msg->databaseid, false);
	if (dbentry == NULL)
	{
		/*
		 * We have no data for this DB.  Enter a write request anyway so that
		 * the global stats will get updated.  This is needed to prevent
		 * backend_read_statsfile from waiting for data that we cannot supply,
		 * in the case of a new DB that nobody has yet reported any stats for.
		 * See the behavior of pgstat_read_db_statsfile_timestamp.
		 */
	}
	else if (msg->clock_time < dbentry->stats_timestamp)
	{
		TimestampTz cur_ts = GetCurrentTimestamp();

		if (cur_ts < dbentry->stats_timestamp)
		{
			/*
			 * Sure enough, time went backwards.  Force a new stats file write
			 * to get back in sync; but first, log a complaint.
			 */
			char	   *writetime;
			char	   *mytime;

			/* Copy because timestamptz_to_str returns a static buffer */
			writetime = pstrdup(timestamptz_to_str(dbentry->stats_timestamp));
			mytime = pstrdup(timestamptz_to_str(cur_ts));
			elog(LOG,
				 "stats_timestamp %s is later than collector's time %s for database %u",
				 writetime, mytime, dbentry->databaseid);
			pfree(writetime);
			pfree(mytime);
		}
		else
		{
			/*
			 * Nope, it's just an old request.  Assuming msg's clock_time is
			 * >= its cutoff_time, it must be stale, so we can ignore it.
			 */
			return;
		}
	}
	else if (msg->cutoff_time <= dbentry->stats_timestamp)
	{
		/* Stale request, ignore it */
		return;
	}

	/*
	 * We need to write this DB, so create a request.
	 */
	pending_write_requests = lappend_oid(pending_write_requests,
										 msg->databaseid);
}