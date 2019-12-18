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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  FunctionCall9Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmgr_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

Datum
OidFunctionCall9Coll(Oid functionId, Oid collation, Datum arg1, Datum arg2,
					 Datum arg3, Datum arg4, Datum arg5,
					 Datum arg6, Datum arg7, Datum arg8,
					 Datum arg9)
{
	FmgrInfo	flinfo;

	fmgr_info(functionId, &flinfo);

	return FunctionCall9Coll(&flinfo, collation, arg1, arg2, arg3, arg4, arg5,
							 arg6, arg7, arg8, arg9);
}