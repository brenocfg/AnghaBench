#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ key; } ;
struct TYPE_19__ {int /*<<< orphan*/  nonLeafTupdesc; int /*<<< orphan*/  leafTupdesc; int /*<<< orphan*/ * supportCollation; TYPE_14__* compressFn; } ;
struct TYPE_18__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_17__ {TYPE_1__* rd_att; } ;
struct TYPE_16__ {int natts; } ;
struct TYPE_15__ {int /*<<< orphan*/  fn_oid; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  TYPE_3__* IndexTuple ;
typedef  TYPE_4__ GISTSTATE ;
typedef  TYPE_5__ GISTENTRY ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall1Coll (TYPE_14__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INDEX_MAX_KEYS ; 
 int IndexRelationGetNumberOfKeyAttributes (TYPE_2__*) ; 
 int /*<<< orphan*/  ItemPointerSetOffsetNumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_5__*) ; 
 int /*<<< orphan*/  gistentryinit (TYPE_5__,scalar_t__,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* index_form_tuple (int /*<<< orphan*/ ,scalar_t__*,int*) ; 

IndexTuple
gistFormTuple(GISTSTATE *giststate, Relation r,
			  Datum attdata[], bool isnull[], bool isleaf)
{
	Datum		compatt[INDEX_MAX_KEYS];
	int			i;
	IndexTuple	res;

	/*
	 * Call the compress method on each attribute.
	 */
	for (i = 0; i < IndexRelationGetNumberOfKeyAttributes(r); i++)
	{
		if (isnull[i])
			compatt[i] = (Datum) 0;
		else
		{
			GISTENTRY	centry;
			GISTENTRY  *cep;

			gistentryinit(centry, attdata[i], r, NULL, (OffsetNumber) 0,
						  isleaf);
			/* there may not be a compress function in opclass */
			if (OidIsValid(giststate->compressFn[i].fn_oid))
				cep = (GISTENTRY *)
					DatumGetPointer(FunctionCall1Coll(&giststate->compressFn[i],
													  giststate->supportCollation[i],
													  PointerGetDatum(&centry)));
			else
				cep = &centry;
			compatt[i] = cep->key;
		}
	}

	if (isleaf)
	{
		/*
		 * Emplace each included attribute if any.
		 */
		for (; i < r->rd_att->natts; i++)
		{
			if (isnull[i])
				compatt[i] = (Datum) 0;
			else
				compatt[i] = attdata[i];
		}
	}

	res = index_form_tuple(isleaf ? giststate->leafTupdesc :
						   giststate->nonLeafTupdesc,
						   compatt, isnull);

	/*
	 * The offset number on tuples on internal pages is unused. For historical
	 * reasons, it is set to 0xffff.
	 */
	ItemPointerSetOffsetNumber(&(res->t_tid), 0xffff);
	return res;
}