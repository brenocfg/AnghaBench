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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_11__ {scalar_t__ isnull; TYPE_1__* args; } ;
struct TYPE_10__ {int /*<<< orphan*/  fn_oid; scalar_t__ fn_strict; } ;
struct TYPE_9__ {int isnull; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/ * StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCallInvoke (TYPE_3__*) ; 
 int /*<<< orphan*/  InitFunctionCallInfoData (TYPE_3__,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LOCAL_FCINFO (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* fcinfo ; 

Datum
ReceiveFunctionCall(FmgrInfo *flinfo, StringInfo buf,
					Oid typioparam, int32 typmod)
{
	LOCAL_FCINFO(fcinfo, 3);
	Datum		result;

	if (buf == NULL && flinfo->fn_strict)
		return (Datum) 0;		/* just return null result */

	InitFunctionCallInfoData(*fcinfo, flinfo, 3, InvalidOid, NULL, NULL);

	fcinfo->args[0].value = PointerGetDatum(buf);
	fcinfo->args[0].isnull = false;
	fcinfo->args[1].value = ObjectIdGetDatum(typioparam);
	fcinfo->args[1].isnull = false;
	fcinfo->args[2].value = Int32GetDatum(typmod);
	fcinfo->args[2].isnull = false;

	result = FunctionCallInvoke(fcinfo);

	/* Should get null result if and only if buf is NULL */
	if (buf == NULL)
	{
		if (!fcinfo->isnull)
			elog(ERROR, "receive function %u returned non-NULL",
				 flinfo->fn_oid);
	}
	else
	{
		if (fcinfo->isnull)
			elog(ERROR, "receive function %u returned NULL",
				 flinfo->fn_oid);
	}

	return result;
}