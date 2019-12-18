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
typedef  int uint32 ;
struct TYPE_6__ {int /*<<< orphan*/  len; scalar_t__ val; } ;
struct TYPE_5__ {int /*<<< orphan*/  boolean; int /*<<< orphan*/  numeric; TYPE_2__ string; } ;
struct TYPE_7__ {int type; TYPE_1__ val; } ;
typedef  TYPE_3__ JsonbValue ;

/* Variables and functions */
 int DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NumericGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hash_any (unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_numeric ; 
#define  jbvBool 131 
#define  jbvNull 130 
#define  jbvNumeric 129 
#define  jbvString 128 

void
JsonbHashScalarValue(const JsonbValue *scalarVal, uint32 *hash)
{
	uint32		tmp;

	/* Compute hash value for scalarVal */
	switch (scalarVal->type)
	{
		case jbvNull:
			tmp = 0x01;
			break;
		case jbvString:
			tmp = DatumGetUInt32(hash_any((const unsigned char *) scalarVal->val.string.val,
										  scalarVal->val.string.len));
			break;
		case jbvNumeric:
			/* Must hash equal numerics to equal hash codes */
			tmp = DatumGetUInt32(DirectFunctionCall1(hash_numeric,
													 NumericGetDatum(scalarVal->val.numeric)));
			break;
		case jbvBool:
			tmp = scalarVal->val.boolean ? 0x02 : 0x04;

			break;
		default:
			elog(ERROR, "invalid jsonb scalar type");
			tmp = 0;			/* keep compiler quiet */
			break;
	}

	/*
	 * Combine hash values of successive keys, values and elements by rotating
	 * the previous value left 1 bit, then XOR'ing in the new
	 * key/value/element's hash value.
	 */
	*hash = (*hash << 1) | (*hash >> 31);
	*hash ^= tmp;
}