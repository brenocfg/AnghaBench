#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {int /*<<< orphan*/  type; } ;
struct TYPE_27__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_25__ {int /*<<< orphan*/  numeric; } ;
struct TYPE_26__ {TYPE_1__ val; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  Numeric ;
typedef  TYPE_2__ JsonbValue ;
typedef  TYPE_3__ JsonValueList ;
typedef  TYPE_4__ JsonPathItem ;
typedef  int /*<<< orphan*/  JsonPathExecResult ;
typedef  int /*<<< orphan*/  JsonPathExecContext ;
typedef  int /*<<< orphan*/  (* BinaryArithmFunc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_SINGLETON_SQL_JSON_ITEM_REQUIRED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  JsonValueListHead (TYPE_3__*) ; 
 int JsonValueListLength (TYPE_3__*) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  executeItemOptUnwrapResult (int /*<<< orphan*/ *,TYPE_4__*,TYPE_2__*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  executeNextItem (int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*,TYPE_2__*,TYPE_3__*,int) ; 
 TYPE_2__* getScalar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbvNumeric ; 
 int /*<<< orphan*/  jperError ; 
 scalar_t__ jperIsError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jperOk ; 
 int /*<<< orphan*/  jspGetLeftArg (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  jspGetNext (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  jspGetRightArg (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  jspOperationName (int /*<<< orphan*/ ) ; 
 scalar_t__ jspThrowErrors (int /*<<< orphan*/ *) ; 
 TYPE_2__* palloc (int) ; 

__attribute__((used)) static JsonPathExecResult
executeBinaryArithmExpr(JsonPathExecContext *cxt, JsonPathItem *jsp,
						JsonbValue *jb, BinaryArithmFunc func,
						JsonValueList *found)
{
	JsonPathExecResult jper;
	JsonPathItem elem;
	JsonValueList lseq = {0};
	JsonValueList rseq = {0};
	JsonbValue *lval;
	JsonbValue *rval;
	Numeric		res;

	jspGetLeftArg(jsp, &elem);

	/*
	 * XXX: By standard only operands of multiplicative expressions are
	 * unwrapped.  We extend it to other binary arithmetic expressions too.
	 */
	jper = executeItemOptUnwrapResult(cxt, &elem, jb, true, &lseq);
	if (jperIsError(jper))
		return jper;

	jspGetRightArg(jsp, &elem);

	jper = executeItemOptUnwrapResult(cxt, &elem, jb, true, &rseq);
	if (jperIsError(jper))
		return jper;

	if (JsonValueListLength(&lseq) != 1 ||
		!(lval = getScalar(JsonValueListHead(&lseq), jbvNumeric)))
		RETURN_ERROR(ereport(ERROR,
							 (errcode(ERRCODE_SINGLETON_SQL_JSON_ITEM_REQUIRED),
							  errmsg("left operand of jsonpath operator %s is not a single numeric value",
									 jspOperationName(jsp->type)))));

	if (JsonValueListLength(&rseq) != 1 ||
		!(rval = getScalar(JsonValueListHead(&rseq), jbvNumeric)))
		RETURN_ERROR(ereport(ERROR,
							 (errcode(ERRCODE_SINGLETON_SQL_JSON_ITEM_REQUIRED),
							  errmsg("right operand of jsonpath operator %s is not a single numeric value",
									 jspOperationName(jsp->type)))));

	if (jspThrowErrors(cxt))
	{
		res = func(lval->val.numeric, rval->val.numeric, NULL);
	}
	else
	{
		bool		error = false;

		res = func(lval->val.numeric, rval->val.numeric, &error);

		if (error)
			return jperError;
	}

	if (!jspGetNext(jsp, &elem) && !found)
		return jperOk;

	lval = palloc(sizeof(*lval));
	lval->type = jbvNumeric;
	lval->val.numeric = res;

	return executeNextItem(cxt, jsp, &elem, lval, found, false);
}