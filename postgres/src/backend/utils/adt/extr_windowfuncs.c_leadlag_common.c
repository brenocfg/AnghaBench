#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
typedef  int /*<<< orphan*/  WindowObject ;
struct TYPE_3__ {int /*<<< orphan*/  flinfo; } ;
typedef  TYPE_1__* FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_RETURN_DATUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_RETURN_NULL () ; 
 int /*<<< orphan*/  PG_WINDOW_OBJECT () ; 
 int /*<<< orphan*/  WINDOW_SEEK_CURRENT ; 
 int /*<<< orphan*/  WinGetFuncArgCurrent (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  WinGetFuncArgInPartition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int*,int*) ; 
 int get_fn_expr_arg_stable (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Datum
leadlag_common(FunctionCallInfo fcinfo,
			   bool forward, bool withoffset, bool withdefault)
{
	WindowObject winobj = PG_WINDOW_OBJECT();
	int32		offset;
	bool		const_offset;
	Datum		result;
	bool		isnull;
	bool		isout;

	if (withoffset)
	{
		offset = DatumGetInt32(WinGetFuncArgCurrent(winobj, 1, &isnull));
		if (isnull)
			PG_RETURN_NULL();
		const_offset = get_fn_expr_arg_stable(fcinfo->flinfo, 1);
	}
	else
	{
		offset = 1;
		const_offset = true;
	}

	result = WinGetFuncArgInPartition(winobj, 0,
									  (forward ? offset : -offset),
									  WINDOW_SEEK_CURRENT,
									  const_offset,
									  &isnull, &isout);

	if (isout)
	{
		/*
		 * target row is out of the partition; supply default value if
		 * provided.  otherwise it'll stay NULL
		 */
		if (withdefault)
			result = WinGetFuncArgCurrent(winobj, 2, &isnull);
	}

	if (isnull)
		PG_RETURN_NULL();

	PG_RETURN_DATUM(result);
}