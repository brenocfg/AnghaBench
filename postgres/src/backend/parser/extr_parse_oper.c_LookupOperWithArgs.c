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
typedef  int /*<<< orphan*/  TypeName ;
struct TYPE_3__ {int /*<<< orphan*/  objname; int /*<<< orphan*/  objargs; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectWithArgs ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LookupOperName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  LookupTypeNameOid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lsecond (int /*<<< orphan*/ ) ; 

Oid
LookupOperWithArgs(ObjectWithArgs *oper, bool noError)
{
	TypeName   *oprleft,
			   *oprright;
	Oid			leftoid,
				rightoid;

	Assert(list_length(oper->objargs) == 2);
	oprleft = linitial(oper->objargs);
	oprright = lsecond(oper->objargs);

	if (oprleft == NULL)
		leftoid = InvalidOid;
	else
		leftoid = LookupTypeNameOid(NULL, oprleft, noError);

	if (oprright == NULL)
		rightoid = InvalidOid;
	else
		rightoid = LookupTypeNameOid(NULL, oprright, noError);

	return LookupOperName(NULL, oper->objname, leftoid, rightoid,
						  noError, -1);
}