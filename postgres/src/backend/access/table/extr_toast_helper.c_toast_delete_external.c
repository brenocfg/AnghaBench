#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_9__ {int attlen; } ;
struct TYPE_8__ {TYPE_1__* rd_att; } ;
struct TYPE_7__ {int natts; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 TYPE_5__* TupleDescAttr (TYPE_1__*,int) ; 
 scalar_t__ VARATT_IS_EXTERNAL_ONDISK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toast_delete_datum (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void
toast_delete_external(Relation rel, Datum *values, bool *isnull,
					  bool is_speculative)
{
	TupleDesc	tupleDesc = rel->rd_att;
	int			numAttrs = tupleDesc->natts;
	int			i;

	for (i = 0; i < numAttrs; i++)
	{
		if (TupleDescAttr(tupleDesc, i)->attlen == -1)
		{
			Datum		value = values[i];

			if (isnull[i])
				continue;
			else if (VARATT_IS_EXTERNAL_ONDISK(PointerGetDatum(value)))
				toast_delete_datum(rel, value, is_speculative);
		}
	}
}