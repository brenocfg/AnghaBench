#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ TransactionId ;
struct TYPE_4__ {scalar_t__ relkind; scalar_t__ relfrozenxid; scalar_t__ relminmxid; } ;
struct TYPE_3__ {scalar_t__ datfrozenxid; scalar_t__ datminmxid; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ MultiXactId ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_1__* Form_pg_database ;
typedef  TYPE_2__* Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DATABASEOID ; 
 int /*<<< orphan*/  DatabaseRelationId ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ ForceTransactionIdLimitUpdate () ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 scalar_t__ GetOldestMultiXactId () ; 
 scalar_t__ GetOldestXmin (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int MultiXactIdIsValid (scalar_t__) ; 
 scalar_t__ MultiXactIdPrecedes (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCARRAY_FLAGS_VACUUM ; 
 scalar_t__ RELKIND_MATVIEW ; 
 scalar_t__ RELKIND_RELATION ; 
 scalar_t__ RELKIND_TOASTVALUE ; 
 scalar_t__ ReadNewTransactionId () ; 
 scalar_t__ ReadNextMultiXactId () ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/ * SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TransactionIdIsNormal (scalar_t__) ; 
 scalar_t__ TransactionIdIsValid (scalar_t__) ; 
 scalar_t__ TransactionIdPrecedes (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_inplace_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vac_truncate_clog (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

void
vac_update_datfrozenxid(void)
{
	HeapTuple	tuple;
	Form_pg_database dbform;
	Relation	relation;
	SysScanDesc scan;
	HeapTuple	classTup;
	TransactionId newFrozenXid;
	MultiXactId newMinMulti;
	TransactionId lastSaneFrozenXid;
	MultiXactId lastSaneMinMulti;
	bool		bogus = false;
	bool		dirty = false;

	/*
	 * Initialize the "min" calculation with GetOldestXmin, which is a
	 * reasonable approximation to the minimum relfrozenxid for not-yet-
	 * committed pg_class entries for new tables; see AddNewRelationTuple().
	 * So we cannot produce a wrong minimum by starting with this.
	 */
	newFrozenXid = GetOldestXmin(NULL, PROCARRAY_FLAGS_VACUUM);

	/*
	 * Similarly, initialize the MultiXact "min" with the value that would be
	 * used on pg_class for new tables.  See AddNewRelationTuple().
	 */
	newMinMulti = GetOldestMultiXactId();

	/*
	 * Identify the latest relfrozenxid and relminmxid values that we could
	 * validly see during the scan.  These are conservative values, but it's
	 * not really worth trying to be more exact.
	 */
	lastSaneFrozenXid = ReadNewTransactionId();
	lastSaneMinMulti = ReadNextMultiXactId();

	/*
	 * We must seqscan pg_class to find the minimum Xid, because there is no
	 * index that can help us here.
	 */
	relation = table_open(RelationRelationId, AccessShareLock);

	scan = systable_beginscan(relation, InvalidOid, false,
							  NULL, 0, NULL);

	while ((classTup = systable_getnext(scan)) != NULL)
	{
		Form_pg_class classForm = (Form_pg_class) GETSTRUCT(classTup);

		/*
		 * Only consider relations able to hold unfrozen XIDs (anything else
		 * should have InvalidTransactionId in relfrozenxid anyway).
		 */
		if (classForm->relkind != RELKIND_RELATION &&
			classForm->relkind != RELKIND_MATVIEW &&
			classForm->relkind != RELKIND_TOASTVALUE)
		{
			Assert(!TransactionIdIsValid(classForm->relfrozenxid));
			Assert(!MultiXactIdIsValid(classForm->relminmxid));
			continue;
		}

		/*
		 * Some table AMs might not need per-relation xid / multixid horizons.
		 * It therefore seems reasonable to allow relfrozenxid and relminmxid
		 * to not be set (i.e. set to their respective Invalid*Id)
		 * independently. Thus validate and compute horizon for each only if
		 * set.
		 *
		 * If things are working properly, no relation should have a
		 * relfrozenxid or relminmxid that is "in the future".  However, such
		 * cases have been known to arise due to bugs in pg_upgrade.  If we
		 * see any entries that are "in the future", chicken out and don't do
		 * anything.  This ensures we won't truncate clog & multixact SLRUs
		 * before those relations have been scanned and cleaned up.
		 */

		if (TransactionIdIsValid(classForm->relfrozenxid))
		{
			Assert(TransactionIdIsNormal(classForm->relfrozenxid));

			/* check for values in the future */
			if (TransactionIdPrecedes(lastSaneFrozenXid, classForm->relfrozenxid))
			{
				bogus = true;
				break;
			}

			/* determine new horizon */
			if (TransactionIdPrecedes(classForm->relfrozenxid, newFrozenXid))
				newFrozenXid = classForm->relfrozenxid;
		}

		if (MultiXactIdIsValid(classForm->relminmxid))
		{
			/* check for values in the future */
			if (MultiXactIdPrecedes(lastSaneMinMulti, classForm->relminmxid))
			{
				bogus = true;
				break;
			}

			/* determine new horizon */
			if (MultiXactIdPrecedes(classForm->relminmxid, newMinMulti))
				newMinMulti = classForm->relminmxid;
		}
	}

	/* we're done with pg_class */
	systable_endscan(scan);
	table_close(relation, AccessShareLock);

	/* chicken out if bogus data found */
	if (bogus)
		return;

	Assert(TransactionIdIsNormal(newFrozenXid));
	Assert(MultiXactIdIsValid(newMinMulti));

	/* Now fetch the pg_database tuple we need to update. */
	relation = table_open(DatabaseRelationId, RowExclusiveLock);

	/* Fetch a copy of the tuple to scribble on */
	tuple = SearchSysCacheCopy1(DATABASEOID, ObjectIdGetDatum(MyDatabaseId));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "could not find tuple for database %u", MyDatabaseId);
	dbform = (Form_pg_database) GETSTRUCT(tuple);

	/*
	 * As in vac_update_relstats(), we ordinarily don't want to let
	 * datfrozenxid go backward; but if it's "in the future" then it must be
	 * corrupt and it seems best to overwrite it.
	 */
	if (dbform->datfrozenxid != newFrozenXid &&
		(TransactionIdPrecedes(dbform->datfrozenxid, newFrozenXid) ||
		 TransactionIdPrecedes(lastSaneFrozenXid, dbform->datfrozenxid)))
	{
		dbform->datfrozenxid = newFrozenXid;
		dirty = true;
	}
	else
		newFrozenXid = dbform->datfrozenxid;

	/* Ditto for datminmxid */
	if (dbform->datminmxid != newMinMulti &&
		(MultiXactIdPrecedes(dbform->datminmxid, newMinMulti) ||
		 MultiXactIdPrecedes(lastSaneMinMulti, dbform->datminmxid)))
	{
		dbform->datminmxid = newMinMulti;
		dirty = true;
	}
	else
		newMinMulti = dbform->datminmxid;

	if (dirty)
		heap_inplace_update(relation, tuple);

	heap_freetuple(tuple);
	table_close(relation, RowExclusiveLock);

	/*
	 * If we were able to advance datfrozenxid or datminmxid, see if we can
	 * truncate pg_xact and/or pg_multixact.  Also do it if the shared
	 * XID-wrap-limit info is stale, since this action will update that too.
	 */
	if (dirty || ForceTransactionIdLimitUpdate())
		vac_truncate_clog(newFrozenXid, newMinMulti,
						  lastSaneFrozenXid, lastSaneMinMulti);
}