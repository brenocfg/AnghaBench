#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
struct TYPE_5__ {int /*<<< orphan*/  len; scalar_t__ val; } ;
struct TYPE_6__ {int /*<<< orphan*/  boolean; int /*<<< orphan*/  numeric; TYPE_1__ string; } ;
struct TYPE_7__ {int type; TYPE_2__ val; } ;
typedef  TYPE_3__ JsonbValue ;

/* Variables and functions */
 int /*<<< orphan*/  BoolGetDatum (int /*<<< orphan*/ ) ; 
 int DatumGetUInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NumericGetDatum (int /*<<< orphan*/ ) ; 
 int ROTATE_HIGH_AND_LOW_32BITS (int) ; 
 int /*<<< orphan*/  UInt64GetDatum (int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hash_any_extended (unsigned char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hash_numeric_extended ; 
 int /*<<< orphan*/  hashcharextended ; 
#define  jbvBool 131 
#define  jbvNull 130 
#define  jbvNumeric 129 
#define  jbvString 128 

void
JsonbHashScalarValueExtended(const JsonbValue *scalarVal, uint64 *hash,
							 uint64 seed)
{
	uint64		tmp;

	switch (scalarVal->type)
	{
		case jbvNull:
			tmp = seed + 0x01;
			break;
		case jbvString:
			tmp = DatumGetUInt64(hash_any_extended((const unsigned char *) scalarVal->val.string.val,
												   scalarVal->val.string.len,
												   seed));
			break;
		case jbvNumeric:
			tmp = DatumGetUInt64(DirectFunctionCall2(hash_numeric_extended,
													 NumericGetDatum(scalarVal->val.numeric),
													 UInt64GetDatum(seed)));
			break;
		case jbvBool:
			if (seed)
				tmp = DatumGetUInt64(DirectFunctionCall2(hashcharextended,
														 BoolGetDatum(scalarVal->val.boolean),
														 UInt64GetDatum(seed)));
			else
				tmp = scalarVal->val.boolean ? 0x02 : 0x04;

			break;
		default:
			elog(ERROR, "invalid jsonb scalar type");
			break;
	}

	*hash = ROTATE_HIGH_AND_LOW_32BITS(*hash);
	*hash ^= tmp;
}