#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct varlena {int dummy; } ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_7__ {int attlen; } ;
struct TYPE_6__ {int natts; } ;
typedef  scalar_t__ Pointer ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int MaxTupleAttributeNumber ; 
 int /*<<< orphan*/  PointerGetDatum (struct varlena*) ; 
 TYPE_4__* TupleDescAttr (TYPE_1__*,int) ; 
 scalar_t__ VARATT_IS_EXTERNAL (struct varlena*) ; 
 struct varlena* detoast_external_attr (struct varlena*) ; 
 int /*<<< orphan*/  heap_form_tuple (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 

HeapTuple
toast_build_flattened_tuple(TupleDesc tupleDesc,
							Datum *values,
							bool *isnull)
{
	HeapTuple	new_tuple;
	int			numAttrs = tupleDesc->natts;
	int			num_to_free;
	int			i;
	Datum		new_values[MaxTupleAttributeNumber];
	Pointer		freeable_values[MaxTupleAttributeNumber];

	/*
	 * We can pass the caller's isnull array directly to heap_form_tuple, but
	 * we potentially need to modify the values array.
	 */
	Assert(numAttrs <= MaxTupleAttributeNumber);
	memcpy(new_values, values, numAttrs * sizeof(Datum));

	num_to_free = 0;
	for (i = 0; i < numAttrs; i++)
	{
		/*
		 * Look at non-null varlena attributes
		 */
		if (!isnull[i] && TupleDescAttr(tupleDesc, i)->attlen == -1)
		{
			struct varlena *new_value;

			new_value = (struct varlena *) DatumGetPointer(new_values[i]);
			if (VARATT_IS_EXTERNAL(new_value))
			{
				new_value = detoast_external_attr(new_value);
				new_values[i] = PointerGetDatum(new_value);
				freeable_values[num_to_free++] = (Pointer) new_value;
			}
		}
	}

	/*
	 * Form the reconfigured tuple.
	 */
	new_tuple = heap_form_tuple(tupleDesc, new_values, isnull);

	/*
	 * Free allocated temp values
	 */
	for (i = 0; i < num_to_free; i++)
		pfree(freeable_values[i]);

	return new_tuple;
}