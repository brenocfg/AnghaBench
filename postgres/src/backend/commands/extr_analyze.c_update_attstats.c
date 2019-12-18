#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  float4 ;
struct TYPE_15__ {int* numnumbers; int* numvalues; int* statyplen; char* statypalign; TYPE_1__* attr; int /*<<< orphan*/ * statypbyval; int /*<<< orphan*/ * statypid; scalar_t__** stavalues; int /*<<< orphan*/ ** stanumbers; int /*<<< orphan*/ * stacoll; int /*<<< orphan*/ * staop; int /*<<< orphan*/ * stakind; int /*<<< orphan*/  stadistinct; int /*<<< orphan*/  stawidth; int /*<<< orphan*/  stanullfrac; int /*<<< orphan*/  stats_valid; } ;
typedef  TYPE_2__ VacAttrStats ;
struct TYPE_16__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_14__ {int /*<<< orphan*/  attnum; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__* HeapTuple ;
typedef  scalar_t__ Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int Anum_pg_statistic_staattnum ; 
 int Anum_pg_statistic_stacoll1 ; 
 int Anum_pg_statistic_stadistinct ; 
 int Anum_pg_statistic_stainherit ; 
 int Anum_pg_statistic_stakind1 ; 
 int Anum_pg_statistic_stanullfrac ; 
 int Anum_pg_statistic_stanumbers1 ; 
 int Anum_pg_statistic_staop1 ; 
 int Anum_pg_statistic_starelid ; 
 int Anum_pg_statistic_stavalues1 ; 
 int Anum_pg_statistic_stawidth ; 
 scalar_t__ BoolGetDatum (int) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  FLOAT4OID ; 
 int /*<<< orphan*/  FLOAT4PASSBYVAL ; 
 scalar_t__ Float4GetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (TYPE_3__*) ; 
 scalar_t__ Int16GetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ Int32GetDatum (int /*<<< orphan*/ ) ; 
 int Natts_pg_statistic ; 
 scalar_t__ ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_3__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int STATISTIC_NUM_SLOTS ; 
 int /*<<< orphan*/  STATRELATTINH ; 
 TYPE_3__* SearchSysCache3 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  StatisticRelationId ; 
 int /*<<< orphan*/ * construct_array (scalar_t__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char) ; 
 TYPE_3__* heap_form_tuple (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_3__*) ; 
 TYPE_3__* heap_modify_tuple (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__*,int*,int*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_attstats(Oid relid, bool inh, int natts, VacAttrStats **vacattrstats)
{
	Relation	sd;
	int			attno;

	if (natts <= 0)
		return;					/* nothing to do */

	sd = table_open(StatisticRelationId, RowExclusiveLock);

	for (attno = 0; attno < natts; attno++)
	{
		VacAttrStats *stats = vacattrstats[attno];
		HeapTuple	stup,
					oldtup;
		int			i,
					k,
					n;
		Datum		values[Natts_pg_statistic];
		bool		nulls[Natts_pg_statistic];
		bool		replaces[Natts_pg_statistic];

		/* Ignore attr if we weren't able to collect stats */
		if (!stats->stats_valid)
			continue;

		/*
		 * Construct a new pg_statistic tuple
		 */
		for (i = 0; i < Natts_pg_statistic; ++i)
		{
			nulls[i] = false;
			replaces[i] = true;
		}

		values[Anum_pg_statistic_starelid - 1] = ObjectIdGetDatum(relid);
		values[Anum_pg_statistic_staattnum - 1] = Int16GetDatum(stats->attr->attnum);
		values[Anum_pg_statistic_stainherit - 1] = BoolGetDatum(inh);
		values[Anum_pg_statistic_stanullfrac - 1] = Float4GetDatum(stats->stanullfrac);
		values[Anum_pg_statistic_stawidth - 1] = Int32GetDatum(stats->stawidth);
		values[Anum_pg_statistic_stadistinct - 1] = Float4GetDatum(stats->stadistinct);
		i = Anum_pg_statistic_stakind1 - 1;
		for (k = 0; k < STATISTIC_NUM_SLOTS; k++)
		{
			values[i++] = Int16GetDatum(stats->stakind[k]); /* stakindN */
		}
		i = Anum_pg_statistic_staop1 - 1;
		for (k = 0; k < STATISTIC_NUM_SLOTS; k++)
		{
			values[i++] = ObjectIdGetDatum(stats->staop[k]);	/* staopN */
		}
		i = Anum_pg_statistic_stacoll1 - 1;
		for (k = 0; k < STATISTIC_NUM_SLOTS; k++)
		{
			values[i++] = ObjectIdGetDatum(stats->stacoll[k]);	/* stacollN */
		}
		i = Anum_pg_statistic_stanumbers1 - 1;
		for (k = 0; k < STATISTIC_NUM_SLOTS; k++)
		{
			int			nnum = stats->numnumbers[k];

			if (nnum > 0)
			{
				Datum	   *numdatums = (Datum *) palloc(nnum * sizeof(Datum));
				ArrayType  *arry;

				for (n = 0; n < nnum; n++)
					numdatums[n] = Float4GetDatum(stats->stanumbers[k][n]);
				/* XXX knows more than it should about type float4: */
				arry = construct_array(numdatums, nnum,
									   FLOAT4OID,
									   sizeof(float4), FLOAT4PASSBYVAL, 'i');
				values[i++] = PointerGetDatum(arry);	/* stanumbersN */
			}
			else
			{
				nulls[i] = true;
				values[i++] = (Datum) 0;
			}
		}
		i = Anum_pg_statistic_stavalues1 - 1;
		for (k = 0; k < STATISTIC_NUM_SLOTS; k++)
		{
			if (stats->numvalues[k] > 0)
			{
				ArrayType  *arry;

				arry = construct_array(stats->stavalues[k],
									   stats->numvalues[k],
									   stats->statypid[k],
									   stats->statyplen[k],
									   stats->statypbyval[k],
									   stats->statypalign[k]);
				values[i++] = PointerGetDatum(arry);	/* stavaluesN */
			}
			else
			{
				nulls[i] = true;
				values[i++] = (Datum) 0;
			}
		}

		/* Is there already a pg_statistic tuple for this attribute? */
		oldtup = SearchSysCache3(STATRELATTINH,
								 ObjectIdGetDatum(relid),
								 Int16GetDatum(stats->attr->attnum),
								 BoolGetDatum(inh));

		if (HeapTupleIsValid(oldtup))
		{
			/* Yes, replace it */
			stup = heap_modify_tuple(oldtup,
									 RelationGetDescr(sd),
									 values,
									 nulls,
									 replaces);
			ReleaseSysCache(oldtup);
			CatalogTupleUpdate(sd, &stup->t_self, stup);
		}
		else
		{
			/* No, insert new tuple */
			stup = heap_form_tuple(RelationGetDescr(sd), values, nulls);
			CatalogTupleInsert(sd, stup);
		}

		heap_freetuple(stup);
	}

	table_close(sd, RowExclusiveLock);
}