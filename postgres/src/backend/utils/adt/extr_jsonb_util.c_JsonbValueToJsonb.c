#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int rawScalar; int nElems; } ;
struct TYPE_12__ {TYPE_2__ binary; TYPE_1__ array; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_3__ val; } ;
typedef  TYPE_4__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbParseState ;
typedef  int /*<<< orphan*/  Jsonb ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ IsAJsonbScalar (TYPE_4__*) ; 
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  VARDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 int /*<<< orphan*/  WJB_BEGIN_ARRAY ; 
 int /*<<< orphan*/  WJB_ELEM ; 
 int /*<<< orphan*/  WJB_END_ARRAY ; 
 int /*<<< orphan*/ * convertToJsonb (TYPE_4__*) ; 
 scalar_t__ jbvArray ; 
 scalar_t__ jbvBinary ; 
 scalar_t__ jbvObject ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * palloc (scalar_t__) ; 
 TYPE_4__* pushJsonbValue (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_4__*) ; 

Jsonb *
JsonbValueToJsonb(JsonbValue *val)
{
	Jsonb	   *out;

	if (IsAJsonbScalar(val))
	{
		/* Scalar value */
		JsonbParseState *pstate = NULL;
		JsonbValue *res;
		JsonbValue	scalarArray;

		scalarArray.type = jbvArray;
		scalarArray.val.array.rawScalar = true;
		scalarArray.val.array.nElems = 1;

		pushJsonbValue(&pstate, WJB_BEGIN_ARRAY, &scalarArray);
		pushJsonbValue(&pstate, WJB_ELEM, val);
		res = pushJsonbValue(&pstate, WJB_END_ARRAY, NULL);

		out = convertToJsonb(res);
	}
	else if (val->type == jbvObject || val->type == jbvArray)
	{
		out = convertToJsonb(val);
	}
	else
	{
		Assert(val->type == jbvBinary);
		out = palloc(VARHDRSZ + val->val.binary.len);
		SET_VARSIZE(out, VARHDRSZ + val->val.binary.len);
		memcpy(VARDATA(out), val->val.binary.data, val->val.binary.len);
	}

	return out;
}