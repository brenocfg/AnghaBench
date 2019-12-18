#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  Jsonb ;
typedef  TYPE_1__ JsonValueList ;
typedef  int /*<<< orphan*/  JsonPath ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  JsonbValueToJsonb (int /*<<< orphan*/ ) ; 
 int PG_GETARG_BOOL (int) ; 
 int /*<<< orphan*/ * PG_GETARG_JSONB_P (int) ; 
 int /*<<< orphan*/ * PG_GETARG_JSONPATH_P (int) ; 
 int /*<<< orphan*/  PG_RETURN_JSONB_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  executeJsonPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  wrapItemsInArray (TYPE_1__*) ; 

__attribute__((used)) static Datum
jsonb_path_query_array_internal(FunctionCallInfo fcinfo, bool tz)
{
	Jsonb	   *jb = PG_GETARG_JSONB_P(0);
	JsonPath   *jp = PG_GETARG_JSONPATH_P(1);
	JsonValueList found = {0};
	Jsonb	   *vars = PG_GETARG_JSONB_P(2);
	bool		silent = PG_GETARG_BOOL(3);

	(void) executeJsonPath(jp, vars, jb, !silent, &found, tz);

	PG_RETURN_JSONB_P(JsonbValueToJsonb(wrapItemsInArray(&found)));
}