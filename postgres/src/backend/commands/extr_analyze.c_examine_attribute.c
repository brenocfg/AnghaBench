#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ attstattarget; int tupattnum; scalar_t__ minrows; struct TYPE_13__* attr; int /*<<< orphan*/ * compute_stats; TYPE_3__* attrtype; int /*<<< orphan*/ * statypalign; int /*<<< orphan*/ * statypbyval; int /*<<< orphan*/ * statyplen; int /*<<< orphan*/  attrtypid; int /*<<< orphan*/ * statypid; int /*<<< orphan*/  anl_context; int /*<<< orphan*/  attcollation; int /*<<< orphan*/  attrcollid; int /*<<< orphan*/  atttypmod; int /*<<< orphan*/  attrtypmod; int /*<<< orphan*/  atttypid; scalar_t__ attisdropped; } ;
typedef  TYPE_1__ VacAttrStats ;
struct TYPE_15__ {int /*<<< orphan*/  typanalyze; int /*<<< orphan*/  typalign; int /*<<< orphan*/  typbyval; int /*<<< orphan*/  typlen; } ;
struct TYPE_14__ {int /*<<< orphan*/ * rd_indcollation; int /*<<< orphan*/  rd_att; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_type ;
typedef  TYPE_1__* Form_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  ATTRIBUTE_FIXED_PART_SIZE ; 
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_1__*) ; 
 int STATISTIC_NUM_SLOTS ; 
 int /*<<< orphan*/  SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPEOID ; 
 TYPE_1__* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  anl_context ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exprCollation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprTypmod (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int std_typanalyze (TYPE_1__*) ; 

__attribute__((used)) static VacAttrStats *
examine_attribute(Relation onerel, int attnum, Node *index_expr)
{
	Form_pg_attribute attr = TupleDescAttr(onerel->rd_att, attnum - 1);
	HeapTuple	typtuple;
	VacAttrStats *stats;
	int			i;
	bool		ok;

	/* Never analyze dropped columns */
	if (attr->attisdropped)
		return NULL;

	/* Don't analyze column if user has specified not to */
	if (attr->attstattarget == 0)
		return NULL;

	/*
	 * Create the VacAttrStats struct.  Note that we only have a copy of the
	 * fixed fields of the pg_attribute tuple.
	 */
	stats = (VacAttrStats *) palloc0(sizeof(VacAttrStats));
	stats->attr = (Form_pg_attribute) palloc(ATTRIBUTE_FIXED_PART_SIZE);
	memcpy(stats->attr, attr, ATTRIBUTE_FIXED_PART_SIZE);

	/*
	 * When analyzing an expression index, believe the expression tree's type
	 * not the column datatype --- the latter might be the opckeytype storage
	 * type of the opclass, which is not interesting for our purposes.  (Note:
	 * if we did anything with non-expression index columns, we'd need to
	 * figure out where to get the correct type info from, but for now that's
	 * not a problem.)	It's not clear whether anyone will care about the
	 * typmod, but we store that too just in case.
	 */
	if (index_expr)
	{
		stats->attrtypid = exprType(index_expr);
		stats->attrtypmod = exprTypmod(index_expr);

		/*
		 * If a collation has been specified for the index column, use that in
		 * preference to anything else; but if not, fall back to whatever we
		 * can get from the expression.
		 */
		if (OidIsValid(onerel->rd_indcollation[attnum - 1]))
			stats->attrcollid = onerel->rd_indcollation[attnum - 1];
		else
			stats->attrcollid = exprCollation(index_expr);
	}
	else
	{
		stats->attrtypid = attr->atttypid;
		stats->attrtypmod = attr->atttypmod;
		stats->attrcollid = attr->attcollation;
	}

	typtuple = SearchSysCacheCopy1(TYPEOID,
								   ObjectIdGetDatum(stats->attrtypid));
	if (!HeapTupleIsValid(typtuple))
		elog(ERROR, "cache lookup failed for type %u", stats->attrtypid);
	stats->attrtype = (Form_pg_type) GETSTRUCT(typtuple);
	stats->anl_context = anl_context;
	stats->tupattnum = attnum;

	/*
	 * The fields describing the stats->stavalues[n] element types default to
	 * the type of the data being analyzed, but the type-specific typanalyze
	 * function can change them if it wants to store something else.
	 */
	for (i = 0; i < STATISTIC_NUM_SLOTS; i++)
	{
		stats->statypid[i] = stats->attrtypid;
		stats->statyplen[i] = stats->attrtype->typlen;
		stats->statypbyval[i] = stats->attrtype->typbyval;
		stats->statypalign[i] = stats->attrtype->typalign;
	}

	/*
	 * Call the type-specific typanalyze function.  If none is specified, use
	 * std_typanalyze().
	 */
	if (OidIsValid(stats->attrtype->typanalyze))
		ok = DatumGetBool(OidFunctionCall1(stats->attrtype->typanalyze,
										   PointerGetDatum(stats)));
	else
		ok = std_typanalyze(stats);

	if (!ok || stats->compute_stats == NULL || stats->minrows <= 0)
	{
		heap_freetuple(typtuple);
		pfree(stats->attr);
		pfree(stats);
		return NULL;
	}

	return stats;
}