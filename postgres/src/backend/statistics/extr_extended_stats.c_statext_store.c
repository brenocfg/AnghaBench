#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  replaces ;
typedef  int /*<<< orphan*/  nulls ;
typedef  int /*<<< orphan*/  bytea ;
typedef  int /*<<< orphan*/  VacAttrStats ;
struct TYPE_9__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MVNDistinct ;
typedef  int /*<<< orphan*/  MVDependencies ;
typedef  int /*<<< orphan*/  MCVList ;
typedef  TYPE_1__* HeapTuple ;
typedef  int Datum ;

/* Variables and functions */
 int Anum_pg_statistic_ext_data_stxddependencies ; 
 int Anum_pg_statistic_ext_data_stxdmcv ; 
 int Anum_pg_statistic_ext_data_stxdndistinct ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int Natts_pg_statistic_ext_data ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_1__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  STATEXTDATASTXOID ; 
 TYPE_1__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StatisticExtDataRelationId ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_1__*) ; 
 TYPE_1__* heap_modify_tuple (TYPE_1__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/ * statext_dependencies_serialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * statext_mcv_serialize (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * statext_ndistinct_serialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
statext_store(Oid statOid,
			  MVNDistinct *ndistinct, MVDependencies *dependencies,
			  MCVList *mcv, VacAttrStats **stats)
{
	HeapTuple	stup,
				oldtup;
	Datum		values[Natts_pg_statistic_ext_data];
	bool		nulls[Natts_pg_statistic_ext_data];
	bool		replaces[Natts_pg_statistic_ext_data];
	Relation	pg_stextdata;

	memset(nulls, true, sizeof(nulls));
	memset(replaces, false, sizeof(replaces));
	memset(values, 0, sizeof(values));

	/*
	 * Construct a new pg_statistic_ext_data tuple, replacing the calculated
	 * stats.
	 */
	if (ndistinct != NULL)
	{
		bytea	   *data = statext_ndistinct_serialize(ndistinct);

		nulls[Anum_pg_statistic_ext_data_stxdndistinct - 1] = (data == NULL);
		values[Anum_pg_statistic_ext_data_stxdndistinct - 1] = PointerGetDatum(data);
	}

	if (dependencies != NULL)
	{
		bytea	   *data = statext_dependencies_serialize(dependencies);

		nulls[Anum_pg_statistic_ext_data_stxddependencies - 1] = (data == NULL);
		values[Anum_pg_statistic_ext_data_stxddependencies - 1] = PointerGetDatum(data);
	}
	if (mcv != NULL)
	{
		bytea	   *data = statext_mcv_serialize(mcv, stats);

		nulls[Anum_pg_statistic_ext_data_stxdmcv - 1] = (data == NULL);
		values[Anum_pg_statistic_ext_data_stxdmcv - 1] = PointerGetDatum(data);
	}

	/* always replace the value (either by bytea or NULL) */
	replaces[Anum_pg_statistic_ext_data_stxdndistinct - 1] = true;
	replaces[Anum_pg_statistic_ext_data_stxddependencies - 1] = true;
	replaces[Anum_pg_statistic_ext_data_stxdmcv - 1] = true;

	/* there should already be a pg_statistic_ext_data tuple */
	oldtup = SearchSysCache1(STATEXTDATASTXOID, ObjectIdGetDatum(statOid));
	if (!HeapTupleIsValid(oldtup))
		elog(ERROR, "cache lookup failed for statistics object %u", statOid);

	/* replace it */
	pg_stextdata = table_open(StatisticExtDataRelationId, RowExclusiveLock);

	stup = heap_modify_tuple(oldtup,
							 RelationGetDescr(pg_stextdata),
							 values,
							 nulls,
							 replaces);
	ReleaseSysCache(oldtup);
	CatalogTupleUpdate(pg_stextdata, &stup->t_self, stup);

	heap_freetuple(stup);

	table_close(pg_stextdata, RowExclusiveLock);
}