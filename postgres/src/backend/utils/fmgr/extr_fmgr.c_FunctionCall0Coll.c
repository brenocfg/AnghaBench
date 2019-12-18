#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ isnull; } ;
struct TYPE_8__ {int /*<<< orphan*/  fn_oid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCallInvoke (TYPE_2__*) ; 
 int /*<<< orphan*/  InitFunctionCallInfoData (TYPE_2__,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCAL_FCINFO (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* fcinfo ; 

Datum
FunctionCall0Coll(FmgrInfo *flinfo, Oid collation)
{
	LOCAL_FCINFO(fcinfo, 0);
	Datum		result;

	InitFunctionCallInfoData(*fcinfo, flinfo, 0, collation, NULL, NULL);

	result = FunctionCallInvoke(fcinfo);

	/* Check for null result, since caller is clearly not expecting one */
	if (fcinfo->isnull)
		elog(ERROR, "function %u returned NULL", flinfo->fn_oid);

	return result;
}