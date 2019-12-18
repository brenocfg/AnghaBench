#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * Type ;
struct TYPE_2__ {scalar_t__ typisdefined; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__* Form_pg_type ;

/* Variables and functions */
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * LookupTypeNameExtended (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makeTypeNameFromNameList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  typeTypeId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  typeTypeRelid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Oid
FuncNameAsType(List *funcname)
{
	Oid			result;
	Type		typtup;

	/*
	 * temp_ok=false protects the <refsect1 id="sql-createfunction-security">
	 * contract for writing SECURITY DEFINER functions safely.
	 */
	typtup = LookupTypeNameExtended(NULL, makeTypeNameFromNameList(funcname),
									NULL, false, false);
	if (typtup == NULL)
		return InvalidOid;

	if (((Form_pg_type) GETSTRUCT(typtup))->typisdefined &&
		!OidIsValid(typeTypeRelid(typtup)))
		result = typeTypeId(typtup);
	else
		result = InvalidOid;

	ReleaseSysCache(typtup);
	return result;
}