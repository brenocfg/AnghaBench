#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_31__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_27__ {int /*<<< orphan*/  expr; } ;
struct TYPE_28__ {TYPE_1__ like_regex; } ;
struct TYPE_30__ {int type; TYPE_2__ content; int /*<<< orphan*/  base; } ;
struct TYPE_29__ {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  JsonbValue ;
typedef  TYPE_3__ JsonValueList ;
typedef  TYPE_4__ JsonPathItem ;
typedef  int /*<<< orphan*/  JsonPathExecResult ;
typedef  TYPE_5__ JsonPathExecContext ;
typedef  int /*<<< orphan*/  JsonPathBool ;
typedef  TYPE_5__ JsonLikeRegexContext ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  JsonValueListIsEmpty (TYPE_3__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  executeComparison ; 
 int /*<<< orphan*/  executeItemOptUnwrapResultNoThrow (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int /*<<< orphan*/  executeLikeRegex ; 
 int /*<<< orphan*/  executePredicate (TYPE_5__*,TYPE_4__*,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  executeStartsWith ; 
 int /*<<< orphan*/  jpbFalse ; 
 int /*<<< orphan*/  jpbTrue ; 
 int /*<<< orphan*/  jpbUnknown ; 
 int /*<<< orphan*/  jperIsError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jperOk ; 
#define  jpiAnd 140 
#define  jpiEqual 139 
#define  jpiExists 138 
#define  jpiGreater 137 
#define  jpiGreaterOrEqual 136 
#define  jpiIsUnknown 135 
#define  jpiLess 134 
#define  jpiLessOrEqual 133 
#define  jpiLikeRegex 132 
#define  jpiNot 131 
#define  jpiNotEqual 130 
#define  jpiOr 129 
#define  jpiStartsWith 128 
 int /*<<< orphan*/  jspGetArg (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  jspGetLeftArg (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  jspGetRightArg (TYPE_4__*,TYPE_4__*) ; 
 scalar_t__ jspHasNext (TYPE_4__*) ; 
 int /*<<< orphan*/  jspInitByBuffer (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jspStrictAbsenseOfErrors (TYPE_5__*) ; 

__attribute__((used)) static JsonPathBool
executeBoolItem(JsonPathExecContext *cxt, JsonPathItem *jsp,
				JsonbValue *jb, bool canHaveNext)
{
	JsonPathItem larg;
	JsonPathItem rarg;
	JsonPathBool res;
	JsonPathBool res2;

	if (!canHaveNext && jspHasNext(jsp))
		elog(ERROR, "boolean jsonpath item cannot have next item");

	switch (jsp->type)
	{
		case jpiAnd:
			jspGetLeftArg(jsp, &larg);
			res = executeBoolItem(cxt, &larg, jb, false);

			if (res == jpbFalse)
				return jpbFalse;

			/*
			 * SQL/JSON says that we should check second arg in case of
			 * jperError
			 */

			jspGetRightArg(jsp, &rarg);
			res2 = executeBoolItem(cxt, &rarg, jb, false);

			return res2 == jpbTrue ? res : res2;

		case jpiOr:
			jspGetLeftArg(jsp, &larg);
			res = executeBoolItem(cxt, &larg, jb, false);

			if (res == jpbTrue)
				return jpbTrue;

			jspGetRightArg(jsp, &rarg);
			res2 = executeBoolItem(cxt, &rarg, jb, false);

			return res2 == jpbFalse ? res : res2;

		case jpiNot:
			jspGetArg(jsp, &larg);

			res = executeBoolItem(cxt, &larg, jb, false);

			if (res == jpbUnknown)
				return jpbUnknown;

			return res == jpbTrue ? jpbFalse : jpbTrue;

		case jpiIsUnknown:
			jspGetArg(jsp, &larg);
			res = executeBoolItem(cxt, &larg, jb, false);
			return res == jpbUnknown ? jpbTrue : jpbFalse;

		case jpiEqual:
		case jpiNotEqual:
		case jpiLess:
		case jpiGreater:
		case jpiLessOrEqual:
		case jpiGreaterOrEqual:
			jspGetLeftArg(jsp, &larg);
			jspGetRightArg(jsp, &rarg);
			return executePredicate(cxt, jsp, &larg, &rarg, jb, true,
									executeComparison, cxt);

		case jpiStartsWith:		/* 'whole STARTS WITH initial' */
			jspGetLeftArg(jsp, &larg);	/* 'whole' */
			jspGetRightArg(jsp, &rarg); /* 'initial' */
			return executePredicate(cxt, jsp, &larg, &rarg, jb, false,
									executeStartsWith, NULL);

		case jpiLikeRegex:		/* 'expr LIKE_REGEX pattern FLAGS flags' */
			{
				/*
				 * 'expr' is a sequence-returning expression.  'pattern' is a
				 * regex string literal.  SQL/JSON standard requires XQuery
				 * regexes, but we use Postgres regexes here.  'flags' is a
				 * string literal converted to integer flags at compile-time.
				 */
				JsonLikeRegexContext lrcxt = {0};

				jspInitByBuffer(&larg, jsp->base,
								jsp->content.like_regex.expr);

				return executePredicate(cxt, jsp, &larg, NULL, jb, false,
										executeLikeRegex, &lrcxt);
			}

		case jpiExists:
			jspGetArg(jsp, &larg);

			if (jspStrictAbsenseOfErrors(cxt))
			{
				/*
				 * In strict mode we must get a complete list of values to
				 * check that there are no errors at all.
				 */
				JsonValueList vals = {0};
				JsonPathExecResult res =
				executeItemOptUnwrapResultNoThrow(cxt, &larg, jb,
												  false, &vals);

				if (jperIsError(res))
					return jpbUnknown;

				return JsonValueListIsEmpty(&vals) ? jpbFalse : jpbTrue;
			}
			else
			{
				JsonPathExecResult res =
				executeItemOptUnwrapResultNoThrow(cxt, &larg, jb,
												  false, NULL);

				if (jperIsError(res))
					return jpbUnknown;

				return res == jperOk ? jpbTrue : jpbFalse;
			}

		default:
			elog(ERROR, "invalid boolean jsonpath item type: %d", jsp->type);
			return jpbUnknown;
	}
}