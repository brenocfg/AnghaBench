#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_8__ {int /*<<< orphan*/  typid; int /*<<< orphan*/  value; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
struct TYPE_9__ {TYPE_2__ datetime; TYPE_1__ string; int /*<<< orphan*/  numeric; int /*<<< orphan*/  boolean; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_3__ val; } ;
typedef  TYPE_4__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonPathBool ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int compareDatetime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int compareNumeric (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int compareStrings (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
#define  jbvArray 141 
#define  jbvBinary 140 
#define  jbvBool 139 
#define  jbvDatetime 138 
#define  jbvNull 137 
#define  jbvNumeric 136 
#define  jbvObject 135 
#define  jbvString 134 
 int /*<<< orphan*/  jpbFalse ; 
 int /*<<< orphan*/  jpbTrue ; 
 int /*<<< orphan*/  jpbUnknown ; 
#define  jpiEqual 133 
#define  jpiGreater 132 
#define  jpiGreaterOrEqual 131 
#define  jpiLess 130 
#define  jpiLessOrEqual 129 
#define  jpiNotEqual 128 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static JsonPathBool
compareItems(int32 op, JsonbValue *jb1, JsonbValue *jb2, bool useTz)
{
	int			cmp;
	bool		res;

	if (jb1->type != jb2->type)
	{
		if (jb1->type == jbvNull || jb2->type == jbvNull)

			/*
			 * Equality and order comparison of nulls to non-nulls returns
			 * always false, but inequality comparison returns true.
			 */
			return op == jpiNotEqual ? jpbTrue : jpbFalse;

		/* Non-null items of different types are not comparable. */
		return jpbUnknown;
	}

	switch (jb1->type)
	{
		case jbvNull:
			cmp = 0;
			break;
		case jbvBool:
			cmp = jb1->val.boolean == jb2->val.boolean ? 0 :
				jb1->val.boolean ? 1 : -1;
			break;
		case jbvNumeric:
			cmp = compareNumeric(jb1->val.numeric, jb2->val.numeric);
			break;
		case jbvString:
			if (op == jpiEqual)
				return jb1->val.string.len != jb2->val.string.len ||
					memcmp(jb1->val.string.val,
						   jb2->val.string.val,
						   jb1->val.string.len) ? jpbFalse : jpbTrue;

			cmp = compareStrings(jb1->val.string.val, jb1->val.string.len,
								 jb2->val.string.val, jb2->val.string.len);
			break;
		case jbvDatetime:
			{
				bool		cast_error;

				cmp = compareDatetime(jb1->val.datetime.value,
									  jb1->val.datetime.typid,
									  jb2->val.datetime.value,
									  jb2->val.datetime.typid,
									  useTz,
									  &cast_error);

				if (cast_error)
					return jpbUnknown;
			}
			break;

		case jbvBinary:
		case jbvArray:
		case jbvObject:
			return jpbUnknown;	/* non-scalars are not comparable */

		default:
			elog(ERROR, "invalid jsonb value type %d", jb1->type);
	}

	switch (op)
	{
		case jpiEqual:
			res = (cmp == 0);
			break;
		case jpiNotEqual:
			res = (cmp != 0);
			break;
		case jpiLess:
			res = (cmp < 0);
			break;
		case jpiGreater:
			res = (cmp > 0);
			break;
		case jpiLessOrEqual:
			res = (cmp <= 0);
			break;
		case jpiGreaterOrEqual:
			res = (cmp >= 0);
			break;
		default:
			elog(ERROR, "unrecognized jsonpath operation: %d", op);
			return jpbUnknown;
	}

	return res ? jpbTrue : jpbFalse;
}