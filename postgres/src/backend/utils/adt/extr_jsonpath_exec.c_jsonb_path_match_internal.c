#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  boolean; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__ val; } ;
typedef  TYPE_2__ JsonbValue ;
typedef  int /*<<< orphan*/  Jsonb ;
typedef  TYPE_3__ JsonValueList ;
typedef  int /*<<< orphan*/  JsonPath ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_SINGLETON_SQL_JSON_ITEM_REQUIRED ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_2__* JsonValueListHead (TYPE_3__*) ; 
 int JsonValueListLength (TYPE_3__*) ; 
 int /*<<< orphan*/  PG_FREE_IF_COPY (int /*<<< orphan*/ *,int) ; 
 int PG_GETARG_BOOL (int) ; 
 int /*<<< orphan*/ * PG_GETARG_JSONB_P (int) ; 
 int /*<<< orphan*/ * PG_GETARG_JSONPATH_P (int) ; 
 int PG_NARGS () ; 
 int /*<<< orphan*/  PG_RETURN_BOOL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_RETURN_NULL () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  executeJsonPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_3__*,int) ; 
 scalar_t__ jbvBool ; 
 scalar_t__ jbvNull ; 

__attribute__((used)) static Datum
jsonb_path_match_internal(FunctionCallInfo fcinfo, bool tz)
{
	Jsonb	   *jb = PG_GETARG_JSONB_P(0);
	JsonPath   *jp = PG_GETARG_JSONPATH_P(1);
	JsonValueList found = {0};
	Jsonb	   *vars = NULL;
	bool		silent = true;

	if (PG_NARGS() == 4)
	{
		vars = PG_GETARG_JSONB_P(2);
		silent = PG_GETARG_BOOL(3);
	}

	(void) executeJsonPath(jp, vars, jb, !silent, &found, tz);

	PG_FREE_IF_COPY(jb, 0);
	PG_FREE_IF_COPY(jp, 1);

	if (JsonValueListLength(&found) == 1)
	{
		JsonbValue *jbv = JsonValueListHead(&found);

		if (jbv->type == jbvBool)
			PG_RETURN_BOOL(jbv->val.boolean);

		if (jbv->type == jbvNull)
			PG_RETURN_NULL();
	}

	if (!silent)
		ereport(ERROR,
				(errcode(ERRCODE_SINGLETON_SQL_JSON_ITEM_REQUIRED),
				 errmsg("single boolean result is expected")));

	PG_RETURN_NULL();
}