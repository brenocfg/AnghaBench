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
struct TYPE_2__ {int nextMXact; int multiVacLimit; int multiWarnLimit; int multiStopLimit; int multiWrapLimit; char* oldestMultiXactDB; scalar_t__ nextOffset; scalar_t__ offsetStopLimit; scalar_t__ oldestOffset; scalar_t__ oldestOffsetKnown; } ;
typedef  char* Oid ;
typedef  scalar_t__ MultiXactOffset ;
typedef  int MultiXactId ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExtendMultiXactMember (scalar_t__,int) ; 
 int /*<<< orphan*/  ExtendMultiXactOffset (int) ; 
 int FirstMultiXactId ; 
 scalar_t__ IsUnderPostmaster ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int MULTIXACT_MEMBERS_PER_PAGE ; 
 scalar_t__ MULTIXACT_MEMBER_SAFE_THRESHOLD ; 
 int MXOffsetToMemberPage (scalar_t__) ; 
 int /*<<< orphan*/  MultiXactGenLock ; 
 int /*<<< orphan*/  MultiXactIdPrecedes (int,int) ; 
 scalar_t__ MultiXactOffsetWouldWrap (scalar_t__,scalar_t__,int) ; 
 TYPE_1__* MultiXactState ; 
 int OFFSET_WARN_SEGMENTS ; 
 int /*<<< orphan*/  PMSIGNAL_START_AUTOVAC_LAUNCHER ; 
 scalar_t__ RecoveryInProgress () ; 
 int SLRU_PAGES_PER_SEGMENT ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SendPostmasterSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  debug_elog3 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  debug_elog4 (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_plural (char*,char*,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  errhint (char*,...) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  errmsg_plural (char*,char*,scalar_t__,char*,scalar_t__) ; 
 char* get_database_name (char*) ; 

__attribute__((used)) static MultiXactId
GetNewMultiXactId(int nmembers, MultiXactOffset *offset)
{
	MultiXactId result;
	MultiXactOffset nextOffset;

	debug_elog3(DEBUG2, "GetNew: for %d xids", nmembers);

	/* safety check, we should never get this far in a HS standby */
	if (RecoveryInProgress())
		elog(ERROR, "cannot assign MultiXactIds during recovery");

	LWLockAcquire(MultiXactGenLock, LW_EXCLUSIVE);

	/* Handle wraparound of the nextMXact counter */
	if (MultiXactState->nextMXact < FirstMultiXactId)
		MultiXactState->nextMXact = FirstMultiXactId;

	/* Assign the MXID */
	result = MultiXactState->nextMXact;

	/*----------
	 * Check to see if it's safe to assign another MultiXactId.  This protects
	 * against catastrophic data loss due to multixact wraparound.  The basic
	 * rules are:
	 *
	 * If we're past multiVacLimit or the safe threshold for member storage
	 * space, or we don't know what the safe threshold for member storage is,
	 * start trying to force autovacuum cycles.
	 * If we're past multiWarnLimit, start issuing warnings.
	 * If we're past multiStopLimit, refuse to create new MultiXactIds.
	 *
	 * Note these are pretty much the same protections in GetNewTransactionId.
	 *----------
	 */
	if (!MultiXactIdPrecedes(result, MultiXactState->multiVacLimit))
	{
		/*
		 * For safety's sake, we release MultiXactGenLock while sending
		 * signals, warnings, etc.  This is not so much because we care about
		 * preserving concurrency in this situation, as to avoid any
		 * possibility of deadlock while doing get_database_name(). First,
		 * copy all the shared values we'll need in this path.
		 */
		MultiXactId multiWarnLimit = MultiXactState->multiWarnLimit;
		MultiXactId multiStopLimit = MultiXactState->multiStopLimit;
		MultiXactId multiWrapLimit = MultiXactState->multiWrapLimit;
		Oid			oldest_datoid = MultiXactState->oldestMultiXactDB;

		LWLockRelease(MultiXactGenLock);

		if (IsUnderPostmaster &&
			!MultiXactIdPrecedes(result, multiStopLimit))
		{
			char	   *oldest_datname = get_database_name(oldest_datoid);

			/*
			 * Immediately kick autovacuum into action as we're already in
			 * ERROR territory.
			 */
			SendPostmasterSignal(PMSIGNAL_START_AUTOVAC_LAUNCHER);

			/* complain even if that DB has disappeared */
			if (oldest_datname)
				ereport(ERROR,
						(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
						 errmsg("database is not accepting commands that generate new MultiXactIds to avoid wraparound data loss in database \"%s\"",
								oldest_datname),
						 errhint("Execute a database-wide VACUUM in that database.\n"
								 "You might also need to commit or roll back old prepared transactions, or drop stale replication slots.")));
			else
				ereport(ERROR,
						(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
						 errmsg("database is not accepting commands that generate new MultiXactIds to avoid wraparound data loss in database with OID %u",
								oldest_datoid),
						 errhint("Execute a database-wide VACUUM in that database.\n"
								 "You might also need to commit or roll back old prepared transactions, or drop stale replication slots.")));
		}

		/*
		 * To avoid swamping the postmaster with signals, we issue the autovac
		 * request only once per 64K multis generated.  This still gives
		 * plenty of chances before we get into real trouble.
		 */
		if (IsUnderPostmaster && (result % 65536) == 0)
			SendPostmasterSignal(PMSIGNAL_START_AUTOVAC_LAUNCHER);

		if (!MultiXactIdPrecedes(result, multiWarnLimit))
		{
			char	   *oldest_datname = get_database_name(oldest_datoid);

			/* complain even if that DB has disappeared */
			if (oldest_datname)
				ereport(WARNING,
						(errmsg_plural("database \"%s\" must be vacuumed before %u more MultiXactId is used",
									   "database \"%s\" must be vacuumed before %u more MultiXactIds are used",
									   multiWrapLimit - result,
									   oldest_datname,
									   multiWrapLimit - result),
						 errhint("Execute a database-wide VACUUM in that database.\n"
								 "You might also need to commit or roll back old prepared transactions, or drop stale replication slots.")));
			else
				ereport(WARNING,
						(errmsg_plural("database with OID %u must be vacuumed before %u more MultiXactId is used",
									   "database with OID %u must be vacuumed before %u more MultiXactIds are used",
									   multiWrapLimit - result,
									   oldest_datoid,
									   multiWrapLimit - result),
						 errhint("Execute a database-wide VACUUM in that database.\n"
								 "You might also need to commit or roll back old prepared transactions, or drop stale replication slots.")));
		}

		/* Re-acquire lock and start over */
		LWLockAcquire(MultiXactGenLock, LW_EXCLUSIVE);
		result = MultiXactState->nextMXact;
		if (result < FirstMultiXactId)
			result = FirstMultiXactId;
	}

	/* Make sure there is room for the MXID in the file.  */
	ExtendMultiXactOffset(result);

	/*
	 * Reserve the members space, similarly to above.  Also, be careful not to
	 * return zero as the starting offset for any multixact. See
	 * GetMultiXactIdMembers() for motivation.
	 */
	nextOffset = MultiXactState->nextOffset;
	if (nextOffset == 0)
	{
		*offset = 1;
		nmembers++;				/* allocate member slot 0 too */
	}
	else
		*offset = nextOffset;

	/*----------
	 * Protect against overrun of the members space as well, with the
	 * following rules:
	 *
	 * If we're past offsetStopLimit, refuse to generate more multis.
	 * If we're close to offsetStopLimit, emit a warning.
	 *
	 * Arbitrarily, we start emitting warnings when we're 20 segments or less
	 * from offsetStopLimit.
	 *
	 * Note we haven't updated the shared state yet, so if we fail at this
	 * point, the multixact ID we grabbed can still be used by the next guy.
	 *
	 * Note that there is no point in forcing autovacuum runs here: the
	 * multixact freeze settings would have to be reduced for that to have any
	 * effect.
	 *----------
	 */
#define OFFSET_WARN_SEGMENTS	20
	if (MultiXactState->oldestOffsetKnown &&
		MultiXactOffsetWouldWrap(MultiXactState->offsetStopLimit, nextOffset,
								 nmembers))
	{
		/* see comment in the corresponding offsets wraparound case */
		SendPostmasterSignal(PMSIGNAL_START_AUTOVAC_LAUNCHER);

		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("multixact \"members\" limit exceeded"),
				 errdetail_plural("This command would create a multixact with %u members, but the remaining space is only enough for %u member.",
								  "This command would create a multixact with %u members, but the remaining space is only enough for %u members.",
								  MultiXactState->offsetStopLimit - nextOffset - 1,
								  nmembers,
								  MultiXactState->offsetStopLimit - nextOffset - 1),
				 errhint("Execute a database-wide VACUUM in database with OID %u with reduced vacuum_multixact_freeze_min_age and vacuum_multixact_freeze_table_age settings.",
						 MultiXactState->oldestMultiXactDB)));
	}

	/*
	 * Check whether we should kick autovacuum into action, to prevent members
	 * wraparound. NB we use a much larger window to trigger autovacuum than
	 * just the warning limit. The warning is just a measure of last resort -
	 * this is in line with GetNewTransactionId's behaviour.
	 */
	if (!MultiXactState->oldestOffsetKnown ||
		(MultiXactState->nextOffset - MultiXactState->oldestOffset
		 > MULTIXACT_MEMBER_SAFE_THRESHOLD))
	{
		/*
		 * To avoid swamping the postmaster with signals, we issue the autovac
		 * request only when crossing a segment boundary. With default
		 * compilation settings that's roughly after 50k members.  This still
		 * gives plenty of chances before we get into real trouble.
		 */
		if ((MXOffsetToMemberPage(nextOffset) / SLRU_PAGES_PER_SEGMENT) !=
			(MXOffsetToMemberPage(nextOffset + nmembers) / SLRU_PAGES_PER_SEGMENT))
			SendPostmasterSignal(PMSIGNAL_START_AUTOVAC_LAUNCHER);
	}

	if (MultiXactState->oldestOffsetKnown &&
		MultiXactOffsetWouldWrap(MultiXactState->offsetStopLimit,
								 nextOffset,
								 nmembers + MULTIXACT_MEMBERS_PER_PAGE * SLRU_PAGES_PER_SEGMENT * OFFSET_WARN_SEGMENTS))
		ereport(WARNING,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg_plural("database with OID %u must be vacuumed before %d more multixact member is used",
							   "database with OID %u must be vacuumed before %d more multixact members are used",
							   MultiXactState->offsetStopLimit - nextOffset + nmembers,
							   MultiXactState->oldestMultiXactDB,
							   MultiXactState->offsetStopLimit - nextOffset + nmembers),
				 errhint("Execute a database-wide VACUUM in that database with reduced vacuum_multixact_freeze_min_age and vacuum_multixact_freeze_table_age settings.")));

	ExtendMultiXactMember(nextOffset, nmembers);

	/*
	 * Critical section from here until caller has written the data into the
	 * just-reserved SLRU space; we don't want to error out with a partly
	 * written MultiXact structure.  (In particular, failing to write our
	 * start offset after advancing nextMXact would effectively corrupt the
	 * previous MultiXact.)
	 */
	START_CRIT_SECTION();

	/*
	 * Advance counters.  As in GetNewTransactionId(), this must not happen
	 * until after file extension has succeeded!
	 *
	 * We don't care about MultiXactId wraparound here; it will be handled by
	 * the next iteration.  But note that nextMXact may be InvalidMultiXactId
	 * or the first value on a segment-beginning page after this routine
	 * exits, so anyone else looking at the variable must be prepared to deal
	 * with either case.  Similarly, nextOffset may be zero, but we won't use
	 * that as the actual start offset of the next multixact.
	 */
	(MultiXactState->nextMXact)++;

	MultiXactState->nextOffset += nmembers;

	LWLockRelease(MultiXactGenLock);

	debug_elog4(DEBUG2, "GetNew: returning %u offset %u", result, *offset);
	return result;
}