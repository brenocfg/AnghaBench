#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_26__ {int nkeys; int /*<<< orphan*/ * pp_eq_oprs; int /*<<< orphan*/ * pk_attnums; } ;
struct TYPE_25__ {TYPE_1__* rd_rel; } ;
struct TYPE_24__ {int /*<<< orphan*/  data; } ;
struct TYPE_23__ {scalar_t__ relkind; } ;
typedef  TYPE_2__ StringInfoData ;
typedef  int /*<<< orphan*/ * SPIPlanPtr ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  RI_QueryKey ;
typedef  TYPE_4__ RI_ConstraintInfo ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int MAX_QUOTED_NAME_LEN ; 
 int MAX_QUOTED_REL_NAME_LEN ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 int /*<<< orphan*/  RIAttName (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RIAttType (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ RI_KEYS_NONE_NULL ; 
 int RI_MAX_NUMKEYS ; 
 int /*<<< orphan*/  RI_PLAN_CHECK_LOOKUPPK_FROM_PK ; 
 int /*<<< orphan*/  RelationGetDescr (TYPE_3__*) ; 
 scalar_t__ SPI_OK_CONNECT ; 
 scalar_t__ SPI_OK_FINISH ; 
 int /*<<< orphan*/  SPI_OK_SELECT ; 
 scalar_t__ SPI_connect () ; 
 scalar_t__ SPI_finish () ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,char*,char const*,char*) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  quoteOneName (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quoteRelationName (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  ri_BuildQueryKey (int /*<<< orphan*/ *,TYPE_4__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ri_FetchPreparedPlan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ri_GenerateQual (TYPE_2__*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ri_NullCheck (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__ const*,int) ; 
 int ri_PerformCheck (TYPE_4__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ri_PlanCheck (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static bool
ri_Check_Pk_Match(Relation pk_rel, Relation fk_rel,
				  TupleTableSlot *oldslot,
				  const RI_ConstraintInfo *riinfo)
{
	SPIPlanPtr	qplan;
	RI_QueryKey qkey;
	bool		result;

	/* Only called for non-null rows */
	Assert(ri_NullCheck(RelationGetDescr(pk_rel), oldslot, riinfo, true) == RI_KEYS_NONE_NULL);

	if (SPI_connect() != SPI_OK_CONNECT)
		elog(ERROR, "SPI_connect failed");

	/*
	 * Fetch or prepare a saved plan for checking PK table with values coming
	 * from a PK row
	 */
	ri_BuildQueryKey(&qkey, riinfo, RI_PLAN_CHECK_LOOKUPPK_FROM_PK);

	if ((qplan = ri_FetchPreparedPlan(&qkey)) == NULL)
	{
		StringInfoData querybuf;
		char		pkrelname[MAX_QUOTED_REL_NAME_LEN];
		char		attname[MAX_QUOTED_NAME_LEN];
		char		paramname[16];
		const char *querysep;
		const char *pk_only;
		Oid			queryoids[RI_MAX_NUMKEYS];

		/* ----------
		 * The query string built is
		 *	SELECT 1 FROM [ONLY] <pktable> x WHERE pkatt1 = $1 [AND ...]
		 *		   FOR KEY SHARE OF x
		 * The type id's for the $ parameters are those of the
		 * PK attributes themselves.
		 * ----------
		 */
		initStringInfo(&querybuf);
		pk_only = pk_rel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE ?
			"" : "ONLY ";
		quoteRelationName(pkrelname, pk_rel);
		appendStringInfo(&querybuf, "SELECT 1 FROM %s%s x",
						 pk_only, pkrelname);
		querysep = "WHERE";
		for (int i = 0; i < riinfo->nkeys; i++)
		{
			Oid			pk_type = RIAttType(pk_rel, riinfo->pk_attnums[i]);

			quoteOneName(attname,
						 RIAttName(pk_rel, riinfo->pk_attnums[i]));
			sprintf(paramname, "$%d", i + 1);
			ri_GenerateQual(&querybuf, querysep,
							attname, pk_type,
							riinfo->pp_eq_oprs[i],
							paramname, pk_type);
			querysep = "AND";
			queryoids[i] = pk_type;
		}
		appendStringInfoString(&querybuf, " FOR KEY SHARE OF x");

		/* Prepare and save the plan */
		qplan = ri_PlanCheck(querybuf.data, riinfo->nkeys, queryoids,
							 &qkey, fk_rel, pk_rel);
	}

	/*
	 * We have a plan now. Run it.
	 */
	result = ri_PerformCheck(riinfo, &qkey, qplan,
							 fk_rel, pk_rel,
							 oldslot, NULL,
							 true,	/* treat like update */
							 SPI_OK_SELECT);

	if (SPI_finish() != SPI_OK_FINISH)
		elog(ERROR, "SPI_finish failed");

	return result;
}