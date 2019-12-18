#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_28__ {int /*<<< orphan*/ * tg_trigslot; TYPE_4__* tg_relation; int /*<<< orphan*/  tg_trigger; } ;
typedef  TYPE_2__ TriggerData ;
struct TYPE_31__ {int nkeys; int /*<<< orphan*/ * pf_eq_oprs; int /*<<< orphan*/ * fk_attnums; int /*<<< orphan*/ * pk_attnums; int /*<<< orphan*/  fk_relid; } ;
struct TYPE_30__ {TYPE_1__* rd_rel; } ;
struct TYPE_29__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_27__ {scalar_t__ relkind; } ;
typedef  TYPE_3__ StringInfoData ;
typedef  int /*<<< orphan*/ * SPIPlanPtr ;
typedef  TYPE_4__* Relation ;
typedef  int /*<<< orphan*/  RI_QueryKey ;
typedef  TYPE_5__ RI_ConstraintInfo ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int MAX_QUOTED_NAME_LEN ; 
 int MAX_QUOTED_REL_NAME_LEN ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RIAttCollation (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RIAttName (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ RIAttType (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int RI_MAX_NUMKEYS ; 
 int /*<<< orphan*/  RI_PLAN_SETDEFAULT_DOUPDATE ; 
 int /*<<< orphan*/  RI_PLAN_SETNULL_DOUPDATE ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 scalar_t__ SPI_OK_CONNECT ; 
 scalar_t__ SPI_OK_FINISH ; 
 int /*<<< orphan*/  SPI_OK_UPDATE ; 
 scalar_t__ SPI_connect () ; 
 scalar_t__ SPI_finish () ; 
 int /*<<< orphan*/  appendBinaryStringInfo (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_3__*,char*,char const*,char*,...) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_collation_isdeterministic (scalar_t__) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  quoteOneName (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quoteRelationName (char*,TYPE_4__*) ; 
 int /*<<< orphan*/  ri_BuildQueryKey (int /*<<< orphan*/ *,TYPE_5__ const*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ri_FetchConstraintInfo (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/ * ri_FetchPreparedPlan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ri_GenerateQual (TYPE_3__*,char const*,char*,scalar_t__,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ri_GenerateQualCollation (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  ri_PerformCheck (TYPE_5__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ri_PlanCheck (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ri_restrict (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  table_close (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Datum
ri_set(TriggerData *trigdata, bool is_set_null)
{
	const RI_ConstraintInfo *riinfo;
	Relation	fk_rel;
	Relation	pk_rel;
	TupleTableSlot *oldslot;
	RI_QueryKey qkey;
	SPIPlanPtr	qplan;

	riinfo = ri_FetchConstraintInfo(trigdata->tg_trigger,
									trigdata->tg_relation, true);

	/*
	 * Get the relation descriptors of the FK and PK tables and the old tuple.
	 *
	 * fk_rel is opened in RowExclusiveLock mode since that's what our
	 * eventual UPDATE will get on it.
	 */
	fk_rel = table_open(riinfo->fk_relid, RowExclusiveLock);
	pk_rel = trigdata->tg_relation;
	oldslot = trigdata->tg_trigslot;

	if (SPI_connect() != SPI_OK_CONNECT)
		elog(ERROR, "SPI_connect failed");

	/*
	 * Fetch or prepare a saved plan for the set null/default operation (it's
	 * the same query for delete and update cases)
	 */
	ri_BuildQueryKey(&qkey, riinfo,
					 (is_set_null
					  ? RI_PLAN_SETNULL_DOUPDATE
					  : RI_PLAN_SETDEFAULT_DOUPDATE));

	if ((qplan = ri_FetchPreparedPlan(&qkey)) == NULL)
	{
		StringInfoData querybuf;
		StringInfoData qualbuf;
		char		fkrelname[MAX_QUOTED_REL_NAME_LEN];
		char		attname[MAX_QUOTED_NAME_LEN];
		char		paramname[16];
		const char *querysep;
		const char *qualsep;
		Oid			queryoids[RI_MAX_NUMKEYS];
		const char *fk_only;

		/* ----------
		 * The query string built is
		 *	UPDATE [ONLY] <fktable> SET fkatt1 = {NULL|DEFAULT} [, ...]
		 *			WHERE $1 = fkatt1 [AND ...]
		 * The type id's for the $ parameters are those of the
		 * corresponding PK attributes.
		 * ----------
		 */
		initStringInfo(&querybuf);
		initStringInfo(&qualbuf);
		fk_only = fk_rel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE ?
			"" : "ONLY ";
		quoteRelationName(fkrelname, fk_rel);
		appendStringInfo(&querybuf, "UPDATE %s%s SET",
						 fk_only, fkrelname);
		querysep = "";
		qualsep = "WHERE";
		for (int i = 0; i < riinfo->nkeys; i++)
		{
			Oid			pk_type = RIAttType(pk_rel, riinfo->pk_attnums[i]);
			Oid			fk_type = RIAttType(fk_rel, riinfo->fk_attnums[i]);
			Oid			pk_coll = RIAttCollation(pk_rel, riinfo->pk_attnums[i]);
			Oid			fk_coll = RIAttCollation(fk_rel, riinfo->fk_attnums[i]);

			quoteOneName(attname,
						 RIAttName(fk_rel, riinfo->fk_attnums[i]));
			appendStringInfo(&querybuf,
							 "%s %s = %s",
							 querysep, attname,
							 is_set_null ? "NULL" : "DEFAULT");
			sprintf(paramname, "$%d", i + 1);
			ri_GenerateQual(&qualbuf, qualsep,
							paramname, pk_type,
							riinfo->pf_eq_oprs[i],
							attname, fk_type);
			if (pk_coll != fk_coll && !get_collation_isdeterministic(pk_coll))
				ri_GenerateQualCollation(&querybuf, pk_coll);
			querysep = ",";
			qualsep = "AND";
			queryoids[i] = pk_type;
		}
		appendBinaryStringInfo(&querybuf, qualbuf.data, qualbuf.len);

		/* Prepare and save the plan */
		qplan = ri_PlanCheck(querybuf.data, riinfo->nkeys, queryoids,
							 &qkey, fk_rel, pk_rel);
	}

	/*
	 * We have a plan now. Run it to update the existing references.
	 */
	ri_PerformCheck(riinfo, &qkey, qplan,
					fk_rel, pk_rel,
					oldslot, NULL,
					true,		/* must detect new rows */
					SPI_OK_UPDATE);

	if (SPI_finish() != SPI_OK_FINISH)
		elog(ERROR, "SPI_finish failed");

	table_close(fk_rel, RowExclusiveLock);

	if (is_set_null)
		return PointerGetDatum(NULL);
	else
	{
		/*
		 * If we just deleted or updated the PK row whose key was equal to the
		 * FK columns' default values, and a referencing row exists in the FK
		 * table, we would have updated that row to the same values it already
		 * had --- and RI_FKey_fk_upd_check_required would hence believe no
		 * check is necessary.  So we need to do another lookup now and in
		 * case a reference still exists, abort the operation.  That is
		 * already implemented in the NO ACTION trigger, so just run it. (This
		 * recheck is only needed in the SET DEFAULT case, since CASCADE would
		 * remove such rows in case of a DELETE operation or would change the
		 * FK key values in case of an UPDATE, while SET NULL is certain to
		 * result in rows that satisfy the FK constraint.)
		 */
		return ri_restrict(trigdata, true);
	}
}