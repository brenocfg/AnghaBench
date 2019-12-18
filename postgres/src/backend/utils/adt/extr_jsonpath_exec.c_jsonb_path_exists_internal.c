#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Jsonb ;
typedef  scalar_t__ JsonPathExecResult ;
typedef  int /*<<< orphan*/  JsonPath ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  PG_FREE_IF_COPY (int /*<<< orphan*/ *,int) ; 
 int PG_GETARG_BOOL (int) ; 
 int /*<<< orphan*/ * PG_GETARG_JSONB_P (int) ; 
 int /*<<< orphan*/ * PG_GETARG_JSONPATH_P (int) ; 
 int PG_NARGS () ; 
 int /*<<< orphan*/  PG_RETURN_BOOL (int) ; 
 int /*<<< orphan*/  PG_RETURN_NULL () ; 
 scalar_t__ executeJsonPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ jperIsError (scalar_t__) ; 
 scalar_t__ jperOk ; 

__attribute__((used)) static Datum
jsonb_path_exists_internal(FunctionCallInfo fcinfo, bool tz)
{
	Jsonb	   *jb = PG_GETARG_JSONB_P(0);
	JsonPath   *jp = PG_GETARG_JSONPATH_P(1);
	JsonPathExecResult res;
	Jsonb	   *vars = NULL;
	bool		silent = true;

	if (PG_NARGS() == 4)
	{
		vars = PG_GETARG_JSONB_P(2);
		silent = PG_GETARG_BOOL(3);
	}

	res = executeJsonPath(jp, vars, jb, !silent, NULL, tz);

	PG_FREE_IF_COPY(jb, 0);
	PG_FREE_IF_COPY(jp, 1);

	if (jperIsError(res))
		PG_RETURN_NULL();

	PG_RETURN_BOOL(res == jperOk);
}