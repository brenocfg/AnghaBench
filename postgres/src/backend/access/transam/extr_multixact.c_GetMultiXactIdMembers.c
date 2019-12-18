#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_14__ {scalar_t__ oldestMultiXactId; scalar_t__ nextMXact; scalar_t__ nextOffset; } ;
struct TYPE_13__ {TYPE_1__* shared; } ;
struct TYPE_12__ {int status; int /*<<< orphan*/  xid; } ;
struct TYPE_11__ {scalar_t__* page_buffer; } ;
typedef  scalar_t__ MultiXactOffset ;
typedef  TYPE_2__ MultiXactMember ;
typedef  scalar_t__ MultiXactId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FirstMultiXactId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int MXACT_MEMBER_XACT_BITMASK ; 
 int MXOffsetToFlagsBitShift (scalar_t__) ; 
 int MXOffsetToFlagsOffset (scalar_t__) ; 
 int MXOffsetToMemberOffset (scalar_t__) ; 
 int MXOffsetToMemberPage (scalar_t__) ; 
 int /*<<< orphan*/  MultiXactGenLock ; 
 int /*<<< orphan*/  MultiXactIdIsValid (scalar_t__) ; 
 scalar_t__ MultiXactIdPrecedes (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MultiXactIdSetOldestVisible () ; 
 int MultiXactIdToOffsetEntry (scalar_t__) ; 
 int MultiXactIdToOffsetPage (scalar_t__) ; 
 int /*<<< orphan*/  MultiXactMemberControlLock ; 
 TYPE_6__* MultiXactMemberCtl ; 
 int /*<<< orphan*/  MultiXactOffsetControlLock ; 
 TYPE_6__* MultiXactOffsetCtl ; 
 TYPE_7__* MultiXactState ; 
 size_t MyBackendId ; 
 scalar_t__* OldestVisibleMXactId ; 
 int SimpleLruReadPage (TYPE_6__*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_elog2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  debug_elog3 (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__) ; 
 int mXactCacheGetById (scalar_t__,TYPE_2__**) ; 
 int /*<<< orphan*/  mXactCachePut (scalar_t__,int,TYPE_2__*) ; 
 scalar_t__ mxid_to_string (scalar_t__,int,TYPE_2__*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pg_usleep (long) ; 

int
GetMultiXactIdMembers(MultiXactId multi, MultiXactMember **members,
					  bool from_pgupgrade, bool onlyLock)
{
	int			pageno;
	int			prev_pageno;
	int			entryno;
	int			slotno;
	MultiXactOffset *offptr;
	MultiXactOffset offset;
	int			length;
	int			truelength;
	int			i;
	MultiXactId oldestMXact;
	MultiXactId nextMXact;
	MultiXactId tmpMXact;
	MultiXactOffset nextOffset;
	MultiXactMember *ptr;

	debug_elog3(DEBUG2, "GetMembers: asked for %u", multi);

	if (!MultiXactIdIsValid(multi) || from_pgupgrade)
		return -1;

	/* See if the MultiXactId is in the local cache */
	length = mXactCacheGetById(multi, members);
	if (length >= 0)
	{
		debug_elog3(DEBUG2, "GetMembers: found %s in the cache",
					mxid_to_string(multi, length, *members));
		return length;
	}

	/* Set our OldestVisibleMXactId[] entry if we didn't already */
	MultiXactIdSetOldestVisible();

	/*
	 * If we know the multi is used only for locking and not for updates, then
	 * we can skip checking if the value is older than our oldest visible
	 * multi.  It cannot possibly still be running.
	 */
	if (onlyLock &&
		MultiXactIdPrecedes(multi, OldestVisibleMXactId[MyBackendId]))
	{
		debug_elog2(DEBUG2, "GetMembers: a locker-only multi is too old");
		*members = NULL;
		return -1;
	}

	/*
	 * We check known limits on MultiXact before resorting to the SLRU area.
	 *
	 * An ID older than MultiXactState->oldestMultiXactId cannot possibly be
	 * useful; it has already been removed, or will be removed shortly, by
	 * truncation.  If one is passed, an error is raised.
	 *
	 * Also, an ID >= nextMXact shouldn't ever be seen here; if it is seen, it
	 * implies undetected ID wraparound has occurred.  This raises a hard
	 * error.
	 *
	 * Shared lock is enough here since we aren't modifying any global state.
	 * Acquire it just long enough to grab the current counter values.  We may
	 * need both nextMXact and nextOffset; see below.
	 */
	LWLockAcquire(MultiXactGenLock, LW_SHARED);

	oldestMXact = MultiXactState->oldestMultiXactId;
	nextMXact = MultiXactState->nextMXact;
	nextOffset = MultiXactState->nextOffset;

	LWLockRelease(MultiXactGenLock);

	if (MultiXactIdPrecedes(multi, oldestMXact))
	{
		ereport(ERROR,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("MultiXactId %u does no longer exist -- apparent wraparound",
						multi)));
		return -1;
	}

	if (!MultiXactIdPrecedes(multi, nextMXact))
		ereport(ERROR,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("MultiXactId %u has not been created yet -- apparent wraparound",
						multi)));

	/*
	 * Find out the offset at which we need to start reading MultiXactMembers
	 * and the number of members in the multixact.  We determine the latter as
	 * the difference between this multixact's starting offset and the next
	 * one's.  However, there are some corner cases to worry about:
	 *
	 * 1. This multixact may be the latest one created, in which case there is
	 * no next one to look at.  In this case the nextOffset value we just
	 * saved is the correct endpoint.
	 *
	 * 2. The next multixact may still be in process of being filled in: that
	 * is, another process may have done GetNewMultiXactId but not yet written
	 * the offset entry for that ID.  In that scenario, it is guaranteed that
	 * the offset entry for that multixact exists (because GetNewMultiXactId
	 * won't release MultiXactGenLock until it does) but contains zero
	 * (because we are careful to pre-zero offset pages). Because
	 * GetNewMultiXactId will never return zero as the starting offset for a
	 * multixact, when we read zero as the next multixact's offset, we know we
	 * have this case.  We sleep for a bit and try again.
	 *
	 * 3. Because GetNewMultiXactId increments offset zero to offset one to
	 * handle case #2, there is an ambiguity near the point of offset
	 * wraparound.  If we see next multixact's offset is one, is that our
	 * multixact's actual endpoint, or did it end at zero with a subsequent
	 * increment?  We handle this using the knowledge that if the zero'th
	 * member slot wasn't filled, it'll contain zero, and zero isn't a valid
	 * transaction ID so it can't be a multixact member.  Therefore, if we
	 * read a zero from the members array, just ignore it.
	 *
	 * This is all pretty messy, but the mess occurs only in infrequent corner
	 * cases, so it seems better than holding the MultiXactGenLock for a long
	 * time on every multixact creation.
	 */
retry:
	LWLockAcquire(MultiXactOffsetControlLock, LW_EXCLUSIVE);

	pageno = MultiXactIdToOffsetPage(multi);
	entryno = MultiXactIdToOffsetEntry(multi);

	slotno = SimpleLruReadPage(MultiXactOffsetCtl, pageno, true, multi);
	offptr = (MultiXactOffset *) MultiXactOffsetCtl->shared->page_buffer[slotno];
	offptr += entryno;
	offset = *offptr;

	Assert(offset != 0);

	/*
	 * Use the same increment rule as GetNewMultiXactId(), that is, don't
	 * handle wraparound explicitly until needed.
	 */
	tmpMXact = multi + 1;

	if (nextMXact == tmpMXact)
	{
		/* Corner case 1: there is no next multixact */
		length = nextOffset - offset;
	}
	else
	{
		MultiXactOffset nextMXOffset;

		/* handle wraparound if needed */
		if (tmpMXact < FirstMultiXactId)
			tmpMXact = FirstMultiXactId;

		prev_pageno = pageno;

		pageno = MultiXactIdToOffsetPage(tmpMXact);
		entryno = MultiXactIdToOffsetEntry(tmpMXact);

		if (pageno != prev_pageno)
			slotno = SimpleLruReadPage(MultiXactOffsetCtl, pageno, true, tmpMXact);

		offptr = (MultiXactOffset *) MultiXactOffsetCtl->shared->page_buffer[slotno];
		offptr += entryno;
		nextMXOffset = *offptr;

		if (nextMXOffset == 0)
		{
			/* Corner case 2: next multixact is still being filled in */
			LWLockRelease(MultiXactOffsetControlLock);
			CHECK_FOR_INTERRUPTS();
			pg_usleep(1000L);
			goto retry;
		}

		length = nextMXOffset - offset;
	}

	LWLockRelease(MultiXactOffsetControlLock);

	ptr = (MultiXactMember *) palloc(length * sizeof(MultiXactMember));
	*members = ptr;

	/* Now get the members themselves. */
	LWLockAcquire(MultiXactMemberControlLock, LW_EXCLUSIVE);

	truelength = 0;
	prev_pageno = -1;
	for (i = 0; i < length; i++, offset++)
	{
		TransactionId *xactptr;
		uint32	   *flagsptr;
		int			flagsoff;
		int			bshift;
		int			memberoff;

		pageno = MXOffsetToMemberPage(offset);
		memberoff = MXOffsetToMemberOffset(offset);

		if (pageno != prev_pageno)
		{
			slotno = SimpleLruReadPage(MultiXactMemberCtl, pageno, true, multi);
			prev_pageno = pageno;
		}

		xactptr = (TransactionId *)
			(MultiXactMemberCtl->shared->page_buffer[slotno] + memberoff);

		if (!TransactionIdIsValid(*xactptr))
		{
			/* Corner case 3: we must be looking at unused slot zero */
			Assert(offset == 0);
			continue;
		}

		flagsoff = MXOffsetToFlagsOffset(offset);
		bshift = MXOffsetToFlagsBitShift(offset);
		flagsptr = (uint32 *) (MultiXactMemberCtl->shared->page_buffer[slotno] + flagsoff);

		ptr[truelength].xid = *xactptr;
		ptr[truelength].status = (*flagsptr >> bshift) & MXACT_MEMBER_XACT_BITMASK;
		truelength++;
	}

	LWLockRelease(MultiXactMemberControlLock);

	/*
	 * Copy the result into the local cache.
	 */
	mXactCachePut(multi, truelength, ptr);

	debug_elog3(DEBUG2, "GetMembers: no cache for %s",
				mxid_to_string(multi, truelength, ptr));
	return truelength;
}