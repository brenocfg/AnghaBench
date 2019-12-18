#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_10__ {int /*<<< orphan*/  relowner; } ;
struct TYPE_9__ {int nkeys; int /*<<< orphan*/  conname; } ;
struct TYPE_8__ {scalar_t__ constr_queryno; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  SPIPlanPtr ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ RI_QueryKey ;
typedef  TYPE_2__ RI_ConstraintInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetLatestSnapshot () ; 
 int /*<<< orphan*/  GetTransactionSnapshot () ; 
 int /*<<< orphan*/  GetUserIdAndSecContext (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  InvalidSnapshot ; 
 scalar_t__ IsolationUsesXactSnapshot () ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int RI_MAX_NUMKEYS ; 
 scalar_t__ RI_PLAN_CHECK_LOOKUPPK ; 
 scalar_t__ RI_PLAN_CHECK_LOOKUPPK_FROM_PK ; 
 scalar_t__ RI_PLAN_LAST_ON_PK ; 
 TYPE_7__* RelationGetForm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int SECURITY_LOCAL_USERID_CHANGE ; 
 int SECURITY_NOFORCE_RLS ; 
 int SPI_OK_SELECT ; 
 int SPI_execute_snapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ SPI_processed ; 
 int /*<<< orphan*/  SPI_result_code_string (int) ; 
 int /*<<< orphan*/  SetUserIdAndSecContext (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ri_ExtractValues (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__ const*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ri_ReportViolation (TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static bool
ri_PerformCheck(const RI_ConstraintInfo *riinfo,
				RI_QueryKey *qkey, SPIPlanPtr qplan,
				Relation fk_rel, Relation pk_rel,
				TupleTableSlot *oldslot, TupleTableSlot *newslot,
				bool detectNewRows, int expect_OK)
{
	Relation	query_rel,
				source_rel;
	bool		source_is_pk;
	Snapshot	test_snapshot;
	Snapshot	crosscheck_snapshot;
	int			limit;
	int			spi_result;
	Oid			save_userid;
	int			save_sec_context;
	Datum		vals[RI_MAX_NUMKEYS * 2];
	char		nulls[RI_MAX_NUMKEYS * 2];

	/*
	 * Use the query type code to determine whether the query is run against
	 * the PK or FK table; we'll do the check as that table's owner
	 */
	if (qkey->constr_queryno <= RI_PLAN_LAST_ON_PK)
		query_rel = pk_rel;
	else
		query_rel = fk_rel;

	/*
	 * The values for the query are taken from the table on which the trigger
	 * is called - it is normally the other one with respect to query_rel. An
	 * exception is ri_Check_Pk_Match(), which uses the PK table for both (and
	 * sets queryno to RI_PLAN_CHECK_LOOKUPPK_FROM_PK).  We might eventually
	 * need some less klugy way to determine this.
	 */
	if (qkey->constr_queryno == RI_PLAN_CHECK_LOOKUPPK)
	{
		source_rel = fk_rel;
		source_is_pk = false;
	}
	else
	{
		source_rel = pk_rel;
		source_is_pk = true;
	}

	/* Extract the parameters to be passed into the query */
	if (newslot)
	{
		ri_ExtractValues(source_rel, newslot, riinfo, source_is_pk,
						 vals, nulls);
		if (oldslot)
			ri_ExtractValues(source_rel, oldslot, riinfo, source_is_pk,
							 vals + riinfo->nkeys, nulls + riinfo->nkeys);
	}
	else
	{
		ri_ExtractValues(source_rel, oldslot, riinfo, source_is_pk,
						 vals, nulls);
	}

	/*
	 * In READ COMMITTED mode, we just need to use an up-to-date regular
	 * snapshot, and we will see all rows that could be interesting. But in
	 * transaction-snapshot mode, we can't change the transaction snapshot. If
	 * the caller passes detectNewRows == false then it's okay to do the query
	 * with the transaction snapshot; otherwise we use a current snapshot, and
	 * tell the executor to error out if it finds any rows under the current
	 * snapshot that wouldn't be visible per the transaction snapshot.  Note
	 * that SPI_execute_snapshot will register the snapshots, so we don't need
	 * to bother here.
	 */
	if (IsolationUsesXactSnapshot() && detectNewRows)
	{
		CommandCounterIncrement();	/* be sure all my own work is visible */
		test_snapshot = GetLatestSnapshot();
		crosscheck_snapshot = GetTransactionSnapshot();
	}
	else
	{
		/* the default SPI behavior is okay */
		test_snapshot = InvalidSnapshot;
		crosscheck_snapshot = InvalidSnapshot;
	}

	/*
	 * If this is a select query (e.g., for a 'no action' or 'restrict'
	 * trigger), we only need to see if there is a single row in the table,
	 * matching the key.  Otherwise, limit = 0 - because we want the query to
	 * affect ALL the matching rows.
	 */
	limit = (expect_OK == SPI_OK_SELECT) ? 1 : 0;

	/* Switch to proper UID to perform check as */
	GetUserIdAndSecContext(&save_userid, &save_sec_context);
	SetUserIdAndSecContext(RelationGetForm(query_rel)->relowner,
						   save_sec_context | SECURITY_LOCAL_USERID_CHANGE |
						   SECURITY_NOFORCE_RLS);

	/* Finally we can run the query. */
	spi_result = SPI_execute_snapshot(qplan,
									  vals, nulls,
									  test_snapshot, crosscheck_snapshot,
									  false, false, limit);

	/* Restore UID and security context */
	SetUserIdAndSecContext(save_userid, save_sec_context);

	/* Check result */
	if (spi_result < 0)
		elog(ERROR, "SPI_execute_snapshot returned %s", SPI_result_code_string(spi_result));

	if (expect_OK >= 0 && spi_result != expect_OK)
		ereport(ERROR,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("referential integrity query on \"%s\" from constraint \"%s\" on \"%s\" gave unexpected result",
						RelationGetRelationName(pk_rel),
						NameStr(riinfo->conname),
						RelationGetRelationName(fk_rel)),
				 errhint("This is most likely due to a rule having rewritten the query.")));

	/* XXX wouldn't it be clearer to do this part at the caller? */
	if (qkey->constr_queryno != RI_PLAN_CHECK_LOOKUPPK_FROM_PK &&
		expect_OK == SPI_OK_SELECT &&
		(SPI_processed == 0) == (qkey->constr_queryno == RI_PLAN_CHECK_LOOKUPPK))
		ri_ReportViolation(riinfo,
						   pk_rel, fk_rel,
						   newslot ? newslot : oldslot,
						   NULL,
						   qkey->constr_queryno, false);

	return SPI_processed != 0;
}