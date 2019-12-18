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
struct TYPE_3__ {int /*<<< orphan*/ * arg; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ DefElem ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LookupFuncName (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OIDOID ; 
 int /*<<< orphan*/  TEXTARRAYOID ; 

__attribute__((used)) static Oid
lookup_fdw_validator_func(DefElem *validator)
{
	Oid			funcargtypes[2];

	if (validator == NULL || validator->arg == NULL)
		return InvalidOid;

	/* validators take text[], oid */
	funcargtypes[0] = TEXTARRAYOID;
	funcargtypes[1] = OIDOID;

	return LookupFuncName((List *) validator->arg, 2, funcargtypes, false);
	/* validator's return value is ignored, so we don't check the type */
}