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
struct TYPE_2__ {char* oldestMultiXactDB; scalar_t__ nextMXact; int /*<<< orphan*/  finishedStartup; scalar_t__ multiWrapLimit; scalar_t__ multiStopLimit; scalar_t__ multiWarnLimit; scalar_t__ multiVacLimit; scalar_t__ oldestMultiXactId; } ;
typedef  char* Oid ;
typedef  scalar_t__ MultiXactId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 scalar_t__ FirstMultiXactId ; 
 int /*<<< orphan*/  InRecovery ; 
 scalar_t__ IsTransactionState () ; 
 scalar_t__ IsUnderPostmaster ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int MaxMultiXactId ; 
 int /*<<< orphan*/  MultiXactGenLock ; 
 int MultiXactIdIsValid (scalar_t__) ; 
 scalar_t__ MultiXactIdPrecedes (scalar_t__,scalar_t__) ; 
 TYPE_1__* MultiXactState ; 
 int /*<<< orphan*/  PMSIGNAL_START_AUTOVAC_LAUNCHER ; 
 int /*<<< orphan*/  SendPostmasterSignal (int /*<<< orphan*/ ) ; 
 int SetOffsetVacuumLimit (int) ; 
 int /*<<< orphan*/  WARNING ; 
 scalar_t__ autovacuum_multixact_freeze_max_age ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  errmsg_plural (char*,char*,scalar_t__,char*,scalar_t__) ; 
 char* get_database_name (char*) ; 

void
SetMultiXactIdLimit(MultiXactId oldest_datminmxid, Oid oldest_datoid,
					bool is_startup)
{
	MultiXactId multiVacLimit;
	MultiXactId multiWarnLimit;
	MultiXactId multiStopLimit;
	MultiXactId multiWrapLimit;
	MultiXactId curMulti;
	bool		needs_offset_vacuum;

	Assert(MultiXactIdIsValid(oldest_datminmxid));

	/*
	 * We pretend that a wrap will happen halfway through the multixact ID
	 * space, but that's not really true, because multixacts wrap differently
	 * from transaction IDs.  Note that, separately from any concern about
	 * multixact IDs wrapping, we must ensure that multixact members do not
	 * wrap.  Limits for that are set in SetOffsetVacuumLimit, not here.
	 */
	multiWrapLimit = oldest_datminmxid + (MaxMultiXactId >> 1);
	if (multiWrapLimit < FirstMultiXactId)
		multiWrapLimit += FirstMultiXactId;

	/*
	 * We'll refuse to continue assigning MultiXactIds once we get within 100
	 * multi of data loss.
	 *
	 * Note: This differs from the magic number used in
	 * SetTransactionIdLimit() since vacuum itself will never generate new
	 * multis.  XXX actually it does, if it needs to freeze old multis.
	 */
	multiStopLimit = multiWrapLimit - 100;
	if (multiStopLimit < FirstMultiXactId)
		multiStopLimit -= FirstMultiXactId;

	/*
	 * We'll start complaining loudly when we get within 10M multis of the
	 * stop point.   This is kind of arbitrary, but if you let your gas gauge
	 * get down to 1% of full, would you be looking for the next gas station?
	 * We need to be fairly liberal about this number because there are lots
	 * of scenarios where most transactions are done by automatic clients that
	 * won't pay attention to warnings. (No, we're not gonna make this
	 * configurable.  If you know enough to configure it, you know enough to
	 * not get in this kind of trouble in the first place.)
	 */
	multiWarnLimit = multiStopLimit - 10000000;
	if (multiWarnLimit < FirstMultiXactId)
		multiWarnLimit -= FirstMultiXactId;

	/*
	 * We'll start trying to force autovacuums when oldest_datminmxid gets to
	 * be more than autovacuum_multixact_freeze_max_age mxids old.
	 *
	 * Note: autovacuum_multixact_freeze_max_age is a PGC_POSTMASTER parameter
	 * so that we don't have to worry about dealing with on-the-fly changes in
	 * its value.  See SetTransactionIdLimit.
	 */
	multiVacLimit = oldest_datminmxid + autovacuum_multixact_freeze_max_age;
	if (multiVacLimit < FirstMultiXactId)
		multiVacLimit += FirstMultiXactId;

	/* Grab lock for just long enough to set the new limit values */
	LWLockAcquire(MultiXactGenLock, LW_EXCLUSIVE);
	MultiXactState->oldestMultiXactId = oldest_datminmxid;
	MultiXactState->oldestMultiXactDB = oldest_datoid;
	MultiXactState->multiVacLimit = multiVacLimit;
	MultiXactState->multiWarnLimit = multiWarnLimit;
	MultiXactState->multiStopLimit = multiStopLimit;
	MultiXactState->multiWrapLimit = multiWrapLimit;
	curMulti = MultiXactState->nextMXact;
	LWLockRelease(MultiXactGenLock);

	/* Log the info */
	ereport(DEBUG1,
			(errmsg("MultiXactId wrap limit is %u, limited by database with OID %u",
					multiWrapLimit, oldest_datoid)));

	/*
	 * Computing the actual limits is only possible once the data directory is
	 * in a consistent state. There's no need to compute the limits while
	 * still replaying WAL - no decisions about new multis are made even
	 * though multixact creations might be replayed. So we'll only do further
	 * checks after TrimMultiXact() has been called.
	 */
	if (!MultiXactState->finishedStartup)
		return;

	Assert(!InRecovery);

	/* Set limits for offset vacuum. */
	needs_offset_vacuum = SetOffsetVacuumLimit(is_startup);

	/*
	 * If past the autovacuum force point, immediately signal an autovac
	 * request.  The reason for this is that autovac only processes one
	 * database per invocation.  Once it's finished cleaning up the oldest
	 * database, it'll call here, and we'll signal the postmaster to start
	 * another iteration immediately if there are still any old databases.
	 */
	if ((MultiXactIdPrecedes(multiVacLimit, curMulti) ||
		 needs_offset_vacuum) && IsUnderPostmaster)
		SendPostmasterSignal(PMSIGNAL_START_AUTOVAC_LAUNCHER);

	/* Give an immediate warning if past the wrap warn point */
	if (MultiXactIdPrecedes(multiWarnLimit, curMulti))
	{
		char	   *oldest_datname;

		/*
		 * We can be called when not inside a transaction, for example during
		 * StartupXLOG().  In such a case we cannot do database access, so we
		 * must just report the oldest DB's OID.
		 *
		 * Note: it's also possible that get_database_name fails and returns
		 * NULL, for example because the database just got dropped.  We'll
		 * still warn, even though the warning might now be unnecessary.
		 */
		if (IsTransactionState())
			oldest_datname = get_database_name(oldest_datoid);
		else
			oldest_datname = NULL;

		if (oldest_datname)
			ereport(WARNING,
					(errmsg_plural("database \"%s\" must be vacuumed before %u more MultiXactId is used",
								   "database \"%s\" must be vacuumed before %u more MultiXactIds are used",
								   multiWrapLimit - curMulti,
								   oldest_datname,
								   multiWrapLimit - curMulti),
					 errhint("To avoid a database shutdown, execute a database-wide VACUUM in that database.\n"
							 "You might also need to commit or roll back old prepared transactions, or drop stale replication slots.")));
		else
			ereport(WARNING,
					(errmsg_plural("database with OID %u must be vacuumed before %u more MultiXactId is used",
								   "database with OID %u must be vacuumed before %u more MultiXactIds are used",
								   multiWrapLimit - curMulti,
								   oldest_datoid,
								   multiWrapLimit - curMulti),
					 errhint("To avoid a database shutdown, execute a database-wide VACUUM in that database.\n"
							 "You might also need to commit or roll back old prepared transactions, or drop stale replication slots.")));
	}
}