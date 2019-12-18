#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  rd_smgr; } ;
typedef  TYPE_1__* Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_TABLE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IndexGetRelation (scalar_t__,int) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_1__*) ; 
 int /*<<< orphan*/  RelationOpenSmgr (TYPE_1__*) ; 
 int /*<<< orphan*/  ShareLock ; 
 int _bt_heapkeyspace (TYPE_1__*) ; 
 int /*<<< orphan*/  bt_check_every_level (TYPE_1__*,TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  btree_index_checkable (TYPE_1__*) ; 
 scalar_t__ btree_index_mainfork_expected (TYPE_1__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* index_open (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smgrexists (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* table_open (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bt_index_check_internal(Oid indrelid, bool parentcheck, bool heapallindexed,
						bool rootdescend)
{
	Oid			heapid;
	Relation	indrel;
	Relation	heaprel;
	LOCKMODE	lockmode;

	if (parentcheck)
		lockmode = ShareLock;
	else
		lockmode = AccessShareLock;

	/*
	 * We must lock table before index to avoid deadlocks.  However, if the
	 * passed indrelid isn't an index then IndexGetRelation() will fail.
	 * Rather than emitting a not-very-helpful error message, postpone
	 * complaining, expecting that the is-it-an-index test below will fail.
	 *
	 * In hot standby mode this will raise an error when parentcheck is true.
	 */
	heapid = IndexGetRelation(indrelid, true);
	if (OidIsValid(heapid))
		heaprel = table_open(heapid, lockmode);
	else
		heaprel = NULL;

	/*
	 * Open the target index relations separately (like relation_openrv(), but
	 * with heap relation locked first to prevent deadlocking).  In hot
	 * standby mode this will raise an error when parentcheck is true.
	 *
	 * There is no need for the usual indcheckxmin usability horizon test
	 * here, even in the heapallindexed case, because index undergoing
	 * verification only needs to have entries for a new transaction snapshot.
	 * (If this is a parentcheck verification, there is no question about
	 * committed or recently dead heap tuples lacking index entries due to
	 * concurrent activity.)
	 */
	indrel = index_open(indrelid, lockmode);

	/*
	 * Since we did the IndexGetRelation call above without any lock, it's
	 * barely possible that a race against an index drop/recreation could have
	 * netted us the wrong table.
	 */
	if (heaprel == NULL || heapid != IndexGetRelation(indrelid, false))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_TABLE),
				 errmsg("could not open parent table of index %s",
						RelationGetRelationName(indrel))));

	/* Relation suitable for checking as B-Tree? */
	btree_index_checkable(indrel);

	if (btree_index_mainfork_expected(indrel))
	{
		bool	heapkeyspace;

		RelationOpenSmgr(indrel);
		if (!smgrexists(indrel->rd_smgr, MAIN_FORKNUM))
			ereport(ERROR,
					(errcode(ERRCODE_INDEX_CORRUPTED),
					 errmsg("index \"%s\" lacks a main relation fork",
							RelationGetRelationName(indrel))));

		/* Check index, possibly against table it is an index on */
		heapkeyspace = _bt_heapkeyspace(indrel);
		bt_check_every_level(indrel, heaprel, heapkeyspace, parentcheck,
							 heapallindexed, rootdescend);
	}

	/*
	 * Release locks early. That's ok here because nothing in the called
	 * routines will trigger shared cache invalidations to be sent, so we can
	 * relax the usual pattern of only releasing locks after commit.
	 */
	index_close(indrel, lockmode);
	if (heaprel)
		table_close(heaprel, lockmode);
}