#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {int /*<<< orphan*/  type; } ;
struct TYPE_26__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_24__ {int /*<<< orphan*/  numeric; } ;
struct TYPE_25__ {TYPE_1__ val; } ;
typedef  scalar_t__ PGFunction ;
typedef  TYPE_2__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonValueListIterator ;
typedef  TYPE_3__ JsonValueList ;
typedef  TYPE_4__ JsonPathItem ;
typedef  scalar_t__ JsonPathExecResult ;
typedef  int /*<<< orphan*/  JsonPathExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetNumeric (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_SQL_JSON_NUMBER_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  JsonValueListInitIterator (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* JsonValueListNext (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NumericGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ executeItemOptUnwrapResult (int /*<<< orphan*/ *,TYPE_4__*,TYPE_2__*,int,TYPE_3__*) ; 
 scalar_t__ executeNextItem (int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*,TYPE_2__*,TYPE_3__*,int) ; 
 TYPE_2__* getScalar (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbvNumeric ; 
 scalar_t__ jperIsError (scalar_t__) ; 
 scalar_t__ jperNotFound ; 
 scalar_t__ jperOk ; 
 int /*<<< orphan*/  jspGetArg (TYPE_4__*,TYPE_4__*) ; 
 int jspGetNext (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  jspOperationName (int /*<<< orphan*/ ) ; 

__attribute__((used)) static JsonPathExecResult
executeUnaryArithmExpr(JsonPathExecContext *cxt, JsonPathItem *jsp,
					   JsonbValue *jb, PGFunction func, JsonValueList *found)
{
	JsonPathExecResult jper;
	JsonPathExecResult jper2;
	JsonPathItem elem;
	JsonValueList seq = {0};
	JsonValueListIterator it;
	JsonbValue *val;
	bool		hasNext;

	jspGetArg(jsp, &elem);
	jper = executeItemOptUnwrapResult(cxt, &elem, jb, true, &seq);

	if (jperIsError(jper))
		return jper;

	jper = jperNotFound;

	hasNext = jspGetNext(jsp, &elem);

	JsonValueListInitIterator(&seq, &it);
	while ((val = JsonValueListNext(&seq, &it)))
	{
		if ((val = getScalar(val, jbvNumeric)))
		{
			if (!found && !hasNext)
				return jperOk;
		}
		else
		{
			if (!found && !hasNext)
				continue;		/* skip non-numerics processing */

			RETURN_ERROR(ereport(ERROR,
								 (errcode(ERRCODE_SQL_JSON_NUMBER_NOT_FOUND),
								  errmsg("operand of unary jsonpath operator %s is not a numeric value",
										 jspOperationName(jsp->type)))));
		}

		if (func)
			val->val.numeric =
				DatumGetNumeric(DirectFunctionCall1(func,
													NumericGetDatum(val->val.numeric)));

		jper2 = executeNextItem(cxt, jsp, &elem, val, found, false);

		if (jperIsError(jper2))
			return jper2;

		if (jper2 == jperOk)
		{
			if (!found)
				return jperOk;
			jper = jperOk;
		}
	}

	return jper;
}