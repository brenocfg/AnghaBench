#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_12__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {int /*<<< orphan*/  numeric; } ;
struct TYPE_11__ {TYPE_1__ val; } ;
typedef  TYPE_2__ JsonbValue ;
typedef  TYPE_3__ JsonValueList ;
typedef  int /*<<< orphan*/  JsonPathItem ;
typedef  int /*<<< orphan*/  JsonPathExecResult ;
typedef  int /*<<< orphan*/  JsonPathExecContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetNumeric (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_SQL_JSON_SUBSCRIPT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JsonValueListHead (TYPE_3__*) ; 
 int JsonValueListLength (TYPE_3__*) ; 
 int /*<<< orphan*/  NumericGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  executeItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 
 TYPE_2__* getScalar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbvNumeric ; 
 scalar_t__ jperIsError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jperOk ; 
 int /*<<< orphan*/  numeric_int4_opt_error (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  numeric_trunc ; 

__attribute__((used)) static JsonPathExecResult
getArrayIndex(JsonPathExecContext *cxt, JsonPathItem *jsp, JsonbValue *jb,
			  int32 *index)
{
	JsonbValue *jbv;
	JsonValueList found = {0};
	JsonPathExecResult res = executeItem(cxt, jsp, jb, &found);
	Datum		numeric_index;
	bool		have_error = false;

	if (jperIsError(res))
		return res;

	if (JsonValueListLength(&found) != 1 ||
		!(jbv = getScalar(JsonValueListHead(&found), jbvNumeric)))
		RETURN_ERROR(ereport(ERROR,
							 (errcode(ERRCODE_INVALID_SQL_JSON_SUBSCRIPT),
							  errmsg("jsonpath array subscript is not a single numeric value"))));

	numeric_index = DirectFunctionCall2(numeric_trunc,
										NumericGetDatum(jbv->val.numeric),
										Int32GetDatum(0));

	*index = numeric_int4_opt_error(DatumGetNumeric(numeric_index),
									&have_error);

	if (have_error)
		RETURN_ERROR(ereport(ERROR,
							 (errcode(ERRCODE_INVALID_SQL_JSON_SUBSCRIPT),
							  errmsg("jsonpath array subscript is out of integer range"))));

	return jperOk;
}