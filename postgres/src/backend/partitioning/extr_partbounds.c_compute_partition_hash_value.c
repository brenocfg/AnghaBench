#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_4__ {int /*<<< orphan*/  fn_oid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetUInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_PARTITION_SEED ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UInt64GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_combine64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64
compute_partition_hash_value(int partnatts, FmgrInfo *partsupfunc, Oid *partcollation,
							 Datum *values, bool *isnull)
{
	int			i;
	uint64		rowHash = 0;
	Datum		seed = UInt64GetDatum(HASH_PARTITION_SEED);

	for (i = 0; i < partnatts; i++)
	{
		/* Nulls are just ignored */
		if (!isnull[i])
		{
			Datum		hash;

			Assert(OidIsValid(partsupfunc[i].fn_oid));

			/*
			 * Compute hash for each datum value by calling respective
			 * datatype-specific hash functions of each partition key
			 * attribute.
			 */
			hash = FunctionCall2Coll(&partsupfunc[i], partcollation[i],
									 values[i], seed);

			/* Form a single 64-bit hash value */
			rowHash = hash_combine64(rowHash, DatumGetUInt64(hash));
		}
	}

	return rowHash;
}