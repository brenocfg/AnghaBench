#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TypeFuncClass ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_5__ {scalar_t__ resultinfo; TYPE_1__* flinfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  fn_expr; int /*<<< orphan*/  fn_oid; } ;
typedef  int /*<<< orphan*/  ReturnSetInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__* FunctionCallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  internal_get_result_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

TypeFuncClass
get_call_result_type(FunctionCallInfo fcinfo,
					 Oid *resultTypeId,
					 TupleDesc *resultTupleDesc)
{
	return internal_get_result_type(fcinfo->flinfo->fn_oid,
									fcinfo->flinfo->fn_expr,
									(ReturnSetInfo *) fcinfo->resultinfo,
									resultTypeId,
									resultTupleDesc);
}