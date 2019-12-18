#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_21__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  workmembuf ;
struct TYPE_32__ {int /*<<< orphan*/  tts_isnull; int /*<<< orphan*/  tts_values; } ;
typedef  TYPE_2__ TupleTableSlot ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  Trigger ;
struct TYPE_35__ {int nkeys; int* fk_attnums; int* pk_attnums; int confmatchtype; int /*<<< orphan*/ * pf_eq_oprs; } ;
struct TYPE_34__ {TYPE_1__* rd_rel; } ;
struct TYPE_33__ {int /*<<< orphan*/  data; } ;
struct TYPE_31__ {int /*<<< orphan*/  tupdesc; int /*<<< orphan*/ * vals; } ;
struct TYPE_30__ {scalar_t__ relkind; } ;
typedef  TYPE_3__ StringInfoData ;
typedef  int /*<<< orphan*/ * SPIPlanPtr ;
typedef  TYPE_4__* Relation ;
typedef  TYPE_5__ RI_ConstraintInfo ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  AtEOXact_GUC (int,int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecStoreVirtualTuple (TYPE_2__*) ; 
#define  FKCONSTR_MATCH_FULL 129 
#define  FKCONSTR_MATCH_SIMPLE 128 
 int /*<<< orphan*/  GUC_ACTION_SAVE ; 
 int /*<<< orphan*/  GetLatestSnapshot () ; 
 int /*<<< orphan*/  InvalidSnapshot ; 
 int /*<<< orphan*/  MAX_QUOTED_NAME_LEN ; 
 int MAX_QUOTED_REL_NAME_LEN ; 
 TYPE_2__* MakeSingleTupleTableSlot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int NewGUCNestLevel () ; 
 int /*<<< orphan*/  PGC_S_SESSION ; 
 int /*<<< orphan*/  PGC_USERSET ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RIAttCollation (TYPE_4__*,int) ; 
 int /*<<< orphan*/  RIAttName (TYPE_4__*,int) ; 
 scalar_t__ RIAttType (TYPE_4__*,int) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_4__*) ; 
 scalar_t__ SPI_OK_CONNECT ; 
 scalar_t__ SPI_OK_FINISH ; 
 int SPI_OK_SELECT ; 
 scalar_t__ SPI_connect () ; 
 int SPI_execute_snapshot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ SPI_finish () ; 
 int /*<<< orphan*/ * SPI_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SPI_processed ; 
 int SPI_result ; 
 int /*<<< orphan*/  SPI_result_code_string (int) ; 
 TYPE_21__* SPI_tuptable ; 
 int /*<<< orphan*/  TTSOpsVirtual ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_3__*,char) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  heap_deform_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_3__*) ; 
 int maintenance_work_mem ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,TYPE_5__ const*,int) ; 
 char* pg_get_partconstrdef_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  quoteOneName (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quoteRelationName (char*,TYPE_4__*) ; 
 TYPE_5__* ri_FetchConstraintInfo (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  ri_GenerateQual (TYPE_3__*,char const*,char*,scalar_t__,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ri_GenerateQualCollation (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  ri_ReportViolation (TYPE_5__*,TYPE_4__*,TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_config_option (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void
RI_PartitionRemove_Check(Trigger *trigger, Relation fk_rel, Relation pk_rel)
{
	const RI_ConstraintInfo *riinfo;
	StringInfoData querybuf;
	char	   *constraintDef;
	char		pkrelname[MAX_QUOTED_REL_NAME_LEN];
	char		fkrelname[MAX_QUOTED_REL_NAME_LEN];
	char		pkattname[MAX_QUOTED_NAME_LEN + 3];
	char		fkattname[MAX_QUOTED_NAME_LEN + 3];
	const char *sep;
	const char *fk_only;
	int			save_nestlevel;
	char		workmembuf[32];
	int			spi_result;
	SPIPlanPtr	qplan;
	int			i;

	riinfo = ri_FetchConstraintInfo(trigger, fk_rel, false);

	/*
	 * We don't check permissions before displaying the error message, on the
	 * assumption that the user detaching the partition must have enough
	 * privileges to examine the table contents anyhow.
	 */

	/*----------
	 * The query string built is:
	 *  SELECT fk.keycols FROM [ONLY] relname fk
	 *    JOIN pkrelname pk
	 *    ON (pk.pkkeycol1=fk.keycol1 [AND ...])
	 *    WHERE (<partition constraint>) AND
	 * For MATCH SIMPLE:
	 *   (fk.keycol1 IS NOT NULL [AND ...])
	 * For MATCH FULL:
	 *   (fk.keycol1 IS NOT NULL [OR ...])
	 *
	 * We attach COLLATE clauses to the operators when comparing columns
	 * that have different collations.
	 *----------
	 */
	initStringInfo(&querybuf);
	appendStringInfoString(&querybuf, "SELECT ");
	sep = "";
	for (i = 0; i < riinfo->nkeys; i++)
	{
		quoteOneName(fkattname,
					 RIAttName(fk_rel, riinfo->fk_attnums[i]));
		appendStringInfo(&querybuf, "%sfk.%s", sep, fkattname);
		sep = ", ";
	}

	quoteRelationName(pkrelname, pk_rel);
	quoteRelationName(fkrelname, fk_rel);
	fk_only = fk_rel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE ?
		"" : "ONLY ";
	appendStringInfo(&querybuf,
					 " FROM %s%s fk JOIN %s pk ON",
					 fk_only, fkrelname, pkrelname);
	strcpy(pkattname, "pk.");
	strcpy(fkattname, "fk.");
	sep = "(";
	for (i = 0; i < riinfo->nkeys; i++)
	{
		Oid			pk_type = RIAttType(pk_rel, riinfo->pk_attnums[i]);
		Oid			fk_type = RIAttType(fk_rel, riinfo->fk_attnums[i]);
		Oid			pk_coll = RIAttCollation(pk_rel, riinfo->pk_attnums[i]);
		Oid			fk_coll = RIAttCollation(fk_rel, riinfo->fk_attnums[i]);

		quoteOneName(pkattname + 3,
					 RIAttName(pk_rel, riinfo->pk_attnums[i]));
		quoteOneName(fkattname + 3,
					 RIAttName(fk_rel, riinfo->fk_attnums[i]));
		ri_GenerateQual(&querybuf, sep,
						pkattname, pk_type,
						riinfo->pf_eq_oprs[i],
						fkattname, fk_type);
		if (pk_coll != fk_coll)
			ri_GenerateQualCollation(&querybuf, pk_coll);
		sep = "AND";
	}

	/*
	 * Start the WHERE clause with the partition constraint (except if this is
	 * the default partition and there's no other partition, because the
	 * partition constraint is the empty string in that case.)
	 */
	constraintDef = pg_get_partconstrdef_string(RelationGetRelid(pk_rel), "pk");
	if (constraintDef && constraintDef[0] != '\0')
		appendStringInfo(&querybuf, ") WHERE %s AND (",
						 constraintDef);
	else
		appendStringInfo(&querybuf, ") WHERE (");

	sep = "";
	for (i = 0; i < riinfo->nkeys; i++)
	{
		quoteOneName(fkattname, RIAttName(fk_rel, riinfo->fk_attnums[i]));
		appendStringInfo(&querybuf,
						 "%sfk.%s IS NOT NULL",
						 sep, fkattname);
		switch (riinfo->confmatchtype)
		{
			case FKCONSTR_MATCH_SIMPLE:
				sep = " AND ";
				break;
			case FKCONSTR_MATCH_FULL:
				sep = " OR ";
				break;
		}
	}
	appendStringInfoChar(&querybuf, ')');

	/*
	 * Temporarily increase work_mem so that the check query can be executed
	 * more efficiently.  It seems okay to do this because the query is simple
	 * enough to not use a multiple of work_mem, and one typically would not
	 * have many large foreign-key validations happening concurrently.  So
	 * this seems to meet the criteria for being considered a "maintenance"
	 * operation, and accordingly we use maintenance_work_mem.
	 *
	 * We use the equivalent of a function SET option to allow the setting to
	 * persist for exactly the duration of the check query.  guc.c also takes
	 * care of undoing the setting on error.
	 */
	save_nestlevel = NewGUCNestLevel();

	snprintf(workmembuf, sizeof(workmembuf), "%d", maintenance_work_mem);
	(void) set_config_option("work_mem", workmembuf,
							 PGC_USERSET, PGC_S_SESSION,
							 GUC_ACTION_SAVE, true, 0, false);

	if (SPI_connect() != SPI_OK_CONNECT)
		elog(ERROR, "SPI_connect failed");

	/*
	 * Generate the plan.  We don't need to cache it, and there are no
	 * arguments to the plan.
	 */
	qplan = SPI_prepare(querybuf.data, 0, NULL);

	if (qplan == NULL)
		elog(ERROR, "SPI_prepare returned %s for %s",
			 SPI_result_code_string(SPI_result), querybuf.data);

	/*
	 * Run the plan.  For safety we force a current snapshot to be used. (In
	 * transaction-snapshot mode, this arguably violates transaction isolation
	 * rules, but we really haven't got much choice.) We don't need to
	 * register the snapshot, because SPI_execute_snapshot will see to it. We
	 * need at most one tuple returned, so pass limit = 1.
	 */
	spi_result = SPI_execute_snapshot(qplan,
									  NULL, NULL,
									  GetLatestSnapshot(),
									  InvalidSnapshot,
									  true, false, 1);

	/* Check result */
	if (spi_result != SPI_OK_SELECT)
		elog(ERROR, "SPI_execute_snapshot returned %s", SPI_result_code_string(spi_result));

	/* Did we find a tuple that would violate the constraint? */
	if (SPI_processed > 0)
	{
		TupleTableSlot *slot;
		HeapTuple	tuple = SPI_tuptable->vals[0];
		TupleDesc	tupdesc = SPI_tuptable->tupdesc;
		RI_ConstraintInfo fake_riinfo;

		slot = MakeSingleTupleTableSlot(tupdesc, &TTSOpsVirtual);

		heap_deform_tuple(tuple, tupdesc,
						  slot->tts_values, slot->tts_isnull);
		ExecStoreVirtualTuple(slot);

		/*
		 * The columns to look at in the result tuple are 1..N, not whatever
		 * they are in the fk_rel.  Hack up riinfo so that ri_ReportViolation
		 * will behave properly.
		 *
		 * In addition to this, we have to pass the correct tupdesc to
		 * ri_ReportViolation, overriding its normal habit of using the pk_rel
		 * or fk_rel's tupdesc.
		 */
		memcpy(&fake_riinfo, riinfo, sizeof(RI_ConstraintInfo));
		for (i = 0; i < fake_riinfo.nkeys; i++)
			fake_riinfo.pk_attnums[i] = i + 1;

		ri_ReportViolation(&fake_riinfo, pk_rel, fk_rel,
						   slot, tupdesc, 0, true);
	}

	if (SPI_finish() != SPI_OK_FINISH)
		elog(ERROR, "SPI_finish failed");

	/*
	 * Restore work_mem.
	 */
	AtEOXact_GUC(true, save_nestlevel);
}