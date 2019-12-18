#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ isnull; TYPE_1__* args; } ;
struct TYPE_10__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_9__ {int isnull; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCallInvoke (TYPE_3__*) ; 
 int /*<<< orphan*/  InitFunctionCallInfoData (TYPE_3__,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCAL_FCINFO (TYPE_3__*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* fcinfo ; 

Datum
FunctionCall1Coll(FmgrInfo *flinfo, Oid collation, Datum arg1)
{
	LOCAL_FCINFO(fcinfo, 1);
	Datum		result;

	InitFunctionCallInfoData(*fcinfo, flinfo, 1, collation, NULL, NULL);

	fcinfo->args[0].value = arg1;
	fcinfo->args[0].isnull = false;

	result = FunctionCallInvoke(fcinfo);

	/* Check for null result, since caller is clearly not expecting one */
	if (fcinfo->isnull)
		elog(ERROR, "function %u returned NULL", flinfo->fn_oid);

	return result;
}