#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_30__ {int /*<<< orphan*/ * tg_trigslot; TYPE_4__* tg_relation; int /*<<< orphan*/  tg_trigger; } ;
typedef  TYPE_2__ TriggerData ;
struct TYPE_33__ {int nkeys; int /*<<< orphan*/ * pf_eq_oprs; int /*<<< orphan*/ * fk_attnums; int /*<<< orphan*/ * pk_attnums; int /*<<< orphan*/  fk_relid; } ;
struct TYPE_32__ {TYPE_1__* rd_rel; } ;
struct TYPE_31__ {int /*<<< orphan*/  data; } ;
struct TYPE_29__ {scalar_t__ relkind; } ;
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
 int /*<<< orphan*/  RI_PLAN_RESTRICT_CHECKREF ; 
 int /*<<< orphan*/  RowShareLock ; 
 scalar_t__ SPI_OK_CONNECT ; 
 scalar_t__ SPI_OK_FINISH ; 
 int /*<<< orphan*/  SPI_OK_SELECT ; 
 scalar_t__ SPI_connect () ; 
 scalar_t__ SPI_finish () ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_3__*,char*,char const*,char*) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_collation_isdeterministic (scalar_t__) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  quoteOneName (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quoteRelationName (char*,TYPE_4__*) ; 
 int /*<<< orphan*/  ri_BuildQueryKey (int /*<<< orphan*/ *,TYPE_5__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ri_Check_Pk_Match (TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ *,TYPE_5__ const*) ; 
 TYPE_5__* ri_FetchConstraintInfo (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/ * ri_FetchPreparedPlan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ri_GenerateQual (TYPE_3__*,char const*,char*,scalar_t__,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ri_GenerateQualCollation (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  ri_PerformCheck (TYPE_5__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ri_PlanCheck (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  table_close (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Datum
ri_restrict(TriggerData *trigdata, bool is_no_action)
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
	 * fk_rel is opened in RowShareLock mode since that's what our eventual
	 * SELECT FOR KEY SHARE will get on it.
	 */
	fk_rel = table_open(riinfo->fk_relid, RowShareLock);
	pk_rel = trigdata->tg_relation;
	oldslot = trigdata->tg_trigslot;

	/*
	 * If another PK row now exists providing the old key values, we should
	 * not do anything.  However, this check should only be made in the NO
	 * ACTION case; in RESTRICT cases we don't wish to allow another row to be
	 * substituted.
	 */
	if (is_no_action &&
		ri_Check_Pk_Match(pk_rel, fk_rel, oldslot, riinfo))
	{
		table_close(fk_rel, RowShareLock);
		return PointerGetDatum(NULL);
	}

	if (SPI_connect() != SPI_OK_CONNECT)
		elog(ERROR, "SPI_connect failed");

	/*
	 * Fetch or prepare a saved plan for the restrict lookup (it's the same
	 * query for delete and update cases)
	 */
	ri_BuildQueryKey(&qkey, riinfo, RI_PLAN_RESTRICT_CHECKREF);

	if ((qplan = ri_FetchPreparedPlan(&qkey)) == NULL)
	{
		StringInfoData querybuf;
		char		fkrelname[MAX_QUOTED_REL_NAME_LEN];
		char		attname[MAX_QUOTED_NAME_LEN];
		char		paramname[16];
		const char *querysep;
		Oid			queryoids[RI_MAX_NUMKEYS];
		const char *fk_only;

		/* ----------
		 * The query string built is
		 *	SELECT 1 FROM [ONLY] <fktable> x WHERE $1 = fkatt1 [AND ...]
		 *		   FOR KEY SHARE OF x
		 * The type id's for the $ parameters are those of the
		 * corresponding PK attributes.
		 * ----------
		 */
		initStringInfo(&querybuf);
		fk_only = fk_rel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE ?
			"" : "ONLY ";
		quoteRelationName(fkrelname, fk_rel);
		appendStringInfo(&querybuf, "SELECT 1 FROM %s%s x",
						 fk_only, fkrelname);
		querysep = "WHERE";
		for (int i = 0; i < riinfo->nkeys; i++)
		{
			Oid			pk_type = RIAttType(pk_rel, riinfo->pk_attnums[i]);
			Oid			fk_type = RIAttType(fk_rel, riinfo->fk_attnums[i]);
			Oid			pk_coll = RIAttCollation(pk_rel, riinfo->pk_attnums[i]);
			Oid			fk_coll = RIAttCollation(fk_rel, riinfo->fk_attnums[i]);

			quoteOneName(attname,
						 RIAttName(fk_rel, riinfo->fk_attnums[i]));
			sprintf(paramname, "$%d", i + 1);
			ri_GenerateQual(&querybuf, querysep,
							paramname, pk_type,
							riinfo->pf_eq_oprs[i],
							attname, fk_type);
			if (pk_coll != fk_coll && !get_collation_isdeterministic(pk_coll))
				ri_GenerateQualCollation(&querybuf, pk_coll);
			querysep = "AND";
			queryoids[i] = pk_type;
		}
		appendStringInfoString(&querybuf, " FOR KEY SHARE OF x");

		/* Prepare and save the plan */
		qplan = ri_PlanCheck(querybuf.data, riinfo->nkeys, queryoids,
							 &qkey, fk_rel, pk_rel);
	}

	/*
	 * We have a plan now. Run it to check for existing references.
	 */
	ri_PerformCheck(riinfo, &qkey, qplan,
					fk_rel, pk_rel,
					oldslot, NULL,
					true,		/* must detect new rows */
					SPI_OK_SELECT);

	if (SPI_finish() != SPI_OK_FINISH)
		elog(ERROR, "SPI_finish failed");

	table_close(fk_rel, RowShareLock);

	return PointerGetDatum(NULL);
}