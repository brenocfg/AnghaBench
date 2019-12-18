#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  type; } ;
struct TYPE_17__ {int /*<<< orphan*/  numeric; } ;
struct TYPE_18__ {TYPE_1__ val; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  PGFunction ;
typedef  TYPE_2__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonValueList ;
typedef  TYPE_3__ JsonPathItem ;
typedef  int /*<<< orphan*/  JsonPathExecResult ;
typedef  int /*<<< orphan*/  JsonPathExecContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetNumeric (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_NON_NUMERIC_SQL_JSON_ITEM ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ JsonbType (TYPE_2__*) ; 
 int /*<<< orphan*/  NumericGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  executeItemUnwrapTargetArray (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  executeNextItem (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* getScalar (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ jbvArray ; 
 int /*<<< orphan*/  jbvNumeric ; 
 int /*<<< orphan*/  jperOk ; 
 int /*<<< orphan*/  jspGetNext (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  jspOperationName (int /*<<< orphan*/ ) ; 
 TYPE_2__* palloc (int) ; 

__attribute__((used)) static JsonPathExecResult
executeNumericItemMethod(JsonPathExecContext *cxt, JsonPathItem *jsp,
						 JsonbValue *jb, bool unwrap, PGFunction func,
						 JsonValueList *found)
{
	JsonPathItem next;
	Datum		datum;

	if (unwrap && JsonbType(jb) == jbvArray)
		return executeItemUnwrapTargetArray(cxt, jsp, jb, found, false);

	if (!(jb = getScalar(jb, jbvNumeric)))
		RETURN_ERROR(ereport(ERROR,
							 (errcode(ERRCODE_NON_NUMERIC_SQL_JSON_ITEM),
							  errmsg("jsonpath item method .%s() can only be applied to a numeric value",
									 jspOperationName(jsp->type)))));

	datum = DirectFunctionCall1(func, NumericGetDatum(jb->val.numeric));

	if (!jspGetNext(jsp, &next) && !found)
		return jperOk;

	jb = palloc(sizeof(*jb));
	jb->type = jbvNumeric;
	jb->val.numeric = DatumGetNumeric(datum);

	return executeNextItem(cxt, jsp, &next, jb, found, false);
}