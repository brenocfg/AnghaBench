#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  fetchTupdesc; int /*<<< orphan*/  leafTupdesc; TYPE_2__* compressFn; TYPE_1__* fetchFn; int /*<<< orphan*/  tempCxt; } ;
struct TYPE_14__ {TYPE_3__* rd_att; } ;
struct TYPE_13__ {int natts; } ;
struct TYPE_12__ {scalar_t__ fn_oid; } ;
struct TYPE_11__ {scalar_t__ fn_oid; } ;
typedef  TYPE_4__* Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_5__ GISTSTATE ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int INDEX_MAX_KEYS ; 
 int IndexRelationGetNumberOfKeyAttributes (TYPE_4__*) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ gistFetchAtt (TYPE_5__*,int,scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 scalar_t__ index_getattr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 

HeapTuple
gistFetchTuple(GISTSTATE *giststate, Relation r, IndexTuple tuple)
{
	MemoryContext oldcxt = MemoryContextSwitchTo(giststate->tempCxt);
	Datum		fetchatt[INDEX_MAX_KEYS];
	bool		isnull[INDEX_MAX_KEYS];
	int			i;

	for (i = 0; i < IndexRelationGetNumberOfKeyAttributes(r); i++)
	{
		Datum		datum;

		datum = index_getattr(tuple, i + 1, giststate->leafTupdesc, &isnull[i]);

		if (giststate->fetchFn[i].fn_oid != InvalidOid)
		{
			if (!isnull[i])
				fetchatt[i] = gistFetchAtt(giststate, i, datum, r);
			else
				fetchatt[i] = (Datum) 0;
		}
		else if (giststate->compressFn[i].fn_oid == InvalidOid)
		{
			/*
			 * If opclass does not provide compress method that could change
			 * original value, att is necessarily stored in original form.
			 */
			if (!isnull[i])
				fetchatt[i] = datum;
			else
				fetchatt[i] = (Datum) 0;
		}
		else
		{
			/*
			 * Index-only scans not supported for this column. Since the
			 * planner chose an index-only scan anyway, it is not interested
			 * in this column, and we can replace it with a NULL.
			 */
			isnull[i] = true;
			fetchatt[i] = (Datum) 0;
		}
	}

	/*
	 * Get each included attribute.
	 */
	for (; i < r->rd_att->natts; i++)
	{
		fetchatt[i] = index_getattr(tuple, i + 1, giststate->leafTupdesc,
									&isnull[i]);
	}
	MemoryContextSwitchTo(oldcxt);

	return heap_form_tuple(giststate->fetchTupdesc, fetchatt, isnull);
}