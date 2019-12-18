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
typedef  int /*<<< orphan*/  TypeFuncClass ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  internal_get_result_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

TypeFuncClass
get_func_result_type(Oid functionId,
					 Oid *resultTypeId,
					 TupleDesc *resultTupleDesc)
{
	return internal_get_result_type(functionId,
									NULL,
									NULL,
									resultTypeId,
									resultTupleDesc);
}