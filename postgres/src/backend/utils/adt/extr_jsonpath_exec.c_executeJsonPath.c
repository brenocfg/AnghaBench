#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int header; } ;
struct TYPE_16__ {scalar_t__ id; int /*<<< orphan*/ * jbc; } ;
struct TYPE_19__ {int laxMode; int ignoreStructuralErrors; int lastGeneratedObjectId; int innermostArraySize; int throwErrors; int useTz; TYPE_1__ baseObject; int /*<<< orphan*/ * current; int /*<<< orphan*/ * root; TYPE_2__* vars; } ;
struct TYPE_18__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_17__ {int /*<<< orphan*/  root; } ;
typedef  int /*<<< orphan*/  JsonbValue ;
typedef  TYPE_2__ Jsonb ;
typedef  TYPE_3__ JsonValueList ;
typedef  int /*<<< orphan*/  JsonPathItem ;
typedef  int /*<<< orphan*/  JsonPathExecResult ;
typedef  TYPE_4__ JsonPathExecContext ;
typedef  TYPE_5__ JsonPath ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int JSONPATH_LAX ; 
 int /*<<< orphan*/  JsonContainerIsObject (int /*<<< orphan*/ *) ; 
 scalar_t__ JsonValueListIsEmpty (TYPE_3__*) ; 
 int /*<<< orphan*/  JsonbExtractScalar (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonbInitBinary (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  executeItem (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ jperIsError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jperNotFound ; 
 int /*<<< orphan*/  jperOk ; 
 int /*<<< orphan*/  jspInit (int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ jspStrictAbsenseOfErrors (TYPE_4__*) ; 

__attribute__((used)) static JsonPathExecResult
executeJsonPath(JsonPath *path, Jsonb *vars, Jsonb *json, bool throwErrors,
				JsonValueList *result, bool useTz)
{
	JsonPathExecContext cxt;
	JsonPathExecResult res;
	JsonPathItem jsp;
	JsonbValue	jbv;

	jspInit(&jsp, path);

	if (!JsonbExtractScalar(&json->root, &jbv))
		JsonbInitBinary(&jbv, json);

	if (vars && !JsonContainerIsObject(&vars->root))
	{
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("\"vars\" argument is not an object"),
				 errdetail("Jsonpath parameters should be encoded as key-value pairs of \"vars\" object.")));
	}

	cxt.vars = vars;
	cxt.laxMode = (path->header & JSONPATH_LAX) != 0;
	cxt.ignoreStructuralErrors = cxt.laxMode;
	cxt.root = &jbv;
	cxt.current = &jbv;
	cxt.baseObject.jbc = NULL;
	cxt.baseObject.id = 0;
	cxt.lastGeneratedObjectId = vars ? 2 : 1;
	cxt.innermostArraySize = -1;
	cxt.throwErrors = throwErrors;
	cxt.useTz = useTz;

	if (jspStrictAbsenseOfErrors(&cxt) && !result)
	{
		/*
		 * In strict mode we must get a complete list of values to check that
		 * there are no errors at all.
		 */
		JsonValueList vals = {0};

		res = executeItem(&cxt, &jsp, &jbv, &vals);

		if (jperIsError(res))
			return res;

		return JsonValueListIsEmpty(&vals) ? jperNotFound : jperOk;
	}

	res = executeItem(&cxt, &jsp, &jbv, result);

	Assert(!throwErrors || !jperIsError(res));

	return res;
}