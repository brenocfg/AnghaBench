#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_8__ {int attlen; int /*<<< orphan*/  attalign; } ;
struct TYPE_7__ {int natts; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ ATT_IS_PACKABLE (TYPE_2__*) ; 
 int /*<<< orphan*/  DatumGetEOHP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ EOH_get_flat_size (int /*<<< orphan*/ ) ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 scalar_t__ VARATT_CAN_MAKE_SHORT (int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_CONVERTED_SHORT_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_IS_EXTERNAL_EXPANDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  att_addlength_datum (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  att_align_datum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  att_align_nominal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Size
heap_compute_data_size(TupleDesc tupleDesc,
					   Datum *values,
					   bool *isnull)
{
	Size		data_length = 0;
	int			i;
	int			numberOfAttributes = tupleDesc->natts;

	for (i = 0; i < numberOfAttributes; i++)
	{
		Datum		val;
		Form_pg_attribute atti;

		if (isnull[i])
			continue;

		val = values[i];
		atti = TupleDescAttr(tupleDesc, i);

		if (ATT_IS_PACKABLE(atti) &&
			VARATT_CAN_MAKE_SHORT(DatumGetPointer(val)))
		{
			/*
			 * we're anticipating converting to a short varlena header, so
			 * adjust length and don't count any alignment
			 */
			data_length += VARATT_CONVERTED_SHORT_SIZE(DatumGetPointer(val));
		}
		else if (atti->attlen == -1 &&
				 VARATT_IS_EXTERNAL_EXPANDED(DatumGetPointer(val)))
		{
			/*
			 * we want to flatten the expanded value so that the constructed
			 * tuple doesn't depend on it
			 */
			data_length = att_align_nominal(data_length, atti->attalign);
			data_length += EOH_get_flat_size(DatumGetEOHP(val));
		}
		else
		{
			data_length = att_align_datum(data_length, atti->attalign,
										  atti->attlen, val);
			data_length = att_addlength_datum(data_length, atti->attlen,
											  val);
		}
	}

	return data_length;
}