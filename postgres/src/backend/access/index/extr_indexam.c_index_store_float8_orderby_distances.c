#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  float4 ;
struct TYPE_6__ {scalar_t__ value; int /*<<< orphan*/  isnull; } ;
struct TYPE_5__ {int xs_recheckorderby; int numberOfOrderBys; int* xs_orderbynulls; void** xs_orderbyvals; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  TYPE_2__ IndexOrderByDistance ;
typedef  void* Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetPointer (void*) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FLOAT4OID ; 
 scalar_t__ FLOAT8OID ; 
 void* Float4GetDatum (int /*<<< orphan*/ ) ; 
 void* Float8GetDatum (scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 

void
index_store_float8_orderby_distances(IndexScanDesc scan, Oid *orderByTypes,
									 IndexOrderByDistance *distances,
									 bool recheckOrderBy)
{
	int			i;

	Assert(distances || !recheckOrderBy);

	scan->xs_recheckorderby = recheckOrderBy;

	for (i = 0; i < scan->numberOfOrderBys; i++)
	{
		if (orderByTypes[i] == FLOAT8OID)
		{
#ifndef USE_FLOAT8_BYVAL
			/* must free any old value to avoid memory leakage */
			if (!scan->xs_orderbynulls[i])
				pfree(DatumGetPointer(scan->xs_orderbyvals[i]));
#endif
			if (distances && !distances[i].isnull)
			{
				scan->xs_orderbyvals[i] = Float8GetDatum(distances[i].value);
				scan->xs_orderbynulls[i] = false;
			}
			else
			{
				scan->xs_orderbyvals[i] = (Datum) 0;
				scan->xs_orderbynulls[i] = true;
			}
		}
		else if (orderByTypes[i] == FLOAT4OID)
		{
			/* convert distance function's result to ORDER BY type */
#ifndef USE_FLOAT4_BYVAL
			/* must free any old value to avoid memory leakage */
			if (!scan->xs_orderbynulls[i])
				pfree(DatumGetPointer(scan->xs_orderbyvals[i]));
#endif
			if (distances && !distances[i].isnull)
			{
				scan->xs_orderbyvals[i] = Float4GetDatum((float4) distances[i].value);
				scan->xs_orderbynulls[i] = false;
			}
			else
			{
				scan->xs_orderbyvals[i] = (Datum) 0;
				scan->xs_orderbynulls[i] = true;
			}
		}
		else
		{
			/*
			 * If the ordering operator's return value is anything else, we
			 * don't know how to convert the float8 bound calculated by the
			 * distance function to that.  The executor won't actually need
			 * the order by values we return here, if there are no lossy
			 * results, so only insist on converting if the *recheck flag is
			 * set.
			 */
			if (scan->xs_recheckorderby)
				elog(ERROR, "ORDER BY operator must return float8 or float4 if the distance function is lossy");
			scan->xs_orderbynulls[i] = true;
		}
	}
}