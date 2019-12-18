#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int32 ;
typedef  scalar_t__ PartitionRangeDatumKind ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PARTITION_RANGE_DATUM_MAXVALUE ; 
 scalar_t__ PARTITION_RANGE_DATUM_MINVALUE ; 

int32
partition_rbound_datum_cmp(FmgrInfo *partsupfunc, Oid *partcollation,
						   Datum *rb_datums, PartitionRangeDatumKind *rb_kind,
						   Datum *tuple_datums, int n_tuple_datums)
{
	int			i;
	int32		cmpval = -1;

	for (i = 0; i < n_tuple_datums; i++)
	{
		if (rb_kind[i] == PARTITION_RANGE_DATUM_MINVALUE)
			return -1;
		else if (rb_kind[i] == PARTITION_RANGE_DATUM_MAXVALUE)
			return 1;

		cmpval = DatumGetInt32(FunctionCall2Coll(&partsupfunc[i],
												 partcollation[i],
												 rb_datums[i],
												 tuple_datums[i]));
		if (cmpval != 0)
			break;
	}

	return cmpval;
}