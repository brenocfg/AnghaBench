#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nmembers; int /*<<< orphan*/  moff; int /*<<< orphan*/  mid; } ;
typedef  TYPE_1__ xl_multixact_create ;
struct TYPE_9__ {int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  MultiXactOffset ;
typedef  TYPE_2__ MultiXactMember ;
typedef  int /*<<< orphan*/  MultiXactId ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetNewMultiXactId (int,int /*<<< orphan*/ *) ; 
 scalar_t__ ISUPDATE_from_mxstatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidMultiXactId ; 
 scalar_t__ MultiXactIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RM_MULTIXACT_ID ; 
 int /*<<< orphan*/  RecordNewMultiXact (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int SizeOfMultiXactCreate ; 
 int /*<<< orphan*/  XLOG_MULTIXACT_CREATE_ID ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  debug_elog2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  debug_elog3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mXactCacheGetBySet (int,TYPE_2__*) ; 
 int /*<<< orphan*/  mXactCachePut (int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  mxid_to_string (int /*<<< orphan*/ ,int,TYPE_2__*) ; 

MultiXactId
MultiXactIdCreateFromMembers(int nmembers, MultiXactMember *members)
{
	MultiXactId multi;
	MultiXactOffset offset;
	xl_multixact_create xlrec;

	debug_elog3(DEBUG2, "Create: %s",
				mxid_to_string(InvalidMultiXactId, nmembers, members));

	/*
	 * See if the same set of members already exists in our cache; if so, just
	 * re-use that MultiXactId.  (Note: it might seem that looking in our
	 * cache is insufficient, and we ought to search disk to see if a
	 * duplicate definition already exists.  But since we only ever create
	 * MultiXacts containing our own XID, in most cases any such MultiXacts
	 * were in fact created by us, and so will be in our cache.  There are
	 * corner cases where someone else added us to a MultiXact without our
	 * knowledge, but it's not worth checking for.)
	 */
	multi = mXactCacheGetBySet(nmembers, members);
	if (MultiXactIdIsValid(multi))
	{
		debug_elog2(DEBUG2, "Create: in cache!");
		return multi;
	}

	/* Verify that there is a single update Xid among the given members. */
	{
		int			i;
		bool		has_update = false;

		for (i = 0; i < nmembers; i++)
		{
			if (ISUPDATE_from_mxstatus(members[i].status))
			{
				if (has_update)
					elog(ERROR, "new multixact has more than one updating member");
				has_update = true;
			}
		}
	}

	/*
	 * Assign the MXID and offsets range to use, and make sure there is space
	 * in the OFFSETs and MEMBERs files.  NB: this routine does
	 * START_CRIT_SECTION().
	 *
	 * Note: unlike MultiXactIdCreate and MultiXactIdExpand, we do not check
	 * that we've called MultiXactIdSetOldestMember here.  This is because
	 * this routine is used in some places to create new MultiXactIds of which
	 * the current backend is not a member, notably during freezing of multis
	 * in vacuum.  During vacuum, in particular, it would be unacceptable to
	 * keep OldestMulti set, in case it runs for long.
	 */
	multi = GetNewMultiXactId(nmembers, &offset);

	/* Make an XLOG entry describing the new MXID. */
	xlrec.mid = multi;
	xlrec.moff = offset;
	xlrec.nmembers = nmembers;

	/*
	 * XXX Note: there's a lot of padding space in MultiXactMember.  We could
	 * find a more compact representation of this Xlog record -- perhaps all
	 * the status flags in one XLogRecData, then all the xids in another one?
	 * Not clear that it's worth the trouble though.
	 */
	XLogBeginInsert();
	XLogRegisterData((char *) (&xlrec), SizeOfMultiXactCreate);
	XLogRegisterData((char *) members, nmembers * sizeof(MultiXactMember));

	(void) XLogInsert(RM_MULTIXACT_ID, XLOG_MULTIXACT_CREATE_ID);

	/* Now enter the information into the OFFSETs and MEMBERs logs */
	RecordNewMultiXact(multi, offset, nmembers, members);

	/* Done with critical section */
	END_CRIT_SECTION();

	/* Store the new MultiXactId in the local cache, too */
	mXactCachePut(multi, nmembers, members);

	debug_elog2(DEBUG2, "Create: all done");

	return multi;
}