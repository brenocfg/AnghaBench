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
struct TYPE_9__ {scalar_t__ isnull; TYPE_1__* args; } ;
struct TYPE_8__ {int isnull; void* value; } ;
typedef  void* (* PGFunction ) (TYPE_2__*) ;
typedef  int /*<<< orphan*/  Oid ;
typedef  void* Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InitFunctionCallInfoData (TYPE_2__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCAL_FCINFO (TYPE_2__*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,void*) ; 
 TYPE_2__* fcinfo ; 
 void* stub1 (TYPE_2__*) ; 

Datum
DirectFunctionCall6Coll(PGFunction func, Oid collation, Datum arg1, Datum arg2,
						Datum arg3, Datum arg4, Datum arg5,
						Datum arg6)
{
	LOCAL_FCINFO(fcinfo, 6);
	Datum		result;

	InitFunctionCallInfoData(*fcinfo, NULL, 6, collation, NULL, NULL);

	fcinfo->args[0].value = arg1;
	fcinfo->args[0].isnull = false;
	fcinfo->args[1].value = arg2;
	fcinfo->args[1].isnull = false;
	fcinfo->args[2].value = arg3;
	fcinfo->args[2].isnull = false;
	fcinfo->args[3].value = arg4;
	fcinfo->args[3].isnull = false;
	fcinfo->args[4].value = arg5;
	fcinfo->args[4].isnull = false;
	fcinfo->args[5].value = arg6;
	fcinfo->args[5].isnull = false;

	result = (*func) (fcinfo);

	/* Check for null result, since caller is clearly not expecting one */
	if (fcinfo->isnull)
		elog(ERROR, "function %p returned NULL", (void *) func);

	return result;
}