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
struct TYPE_3__ {int roletype; int /*<<< orphan*/  rolename; } ;
typedef  TYPE_1__ RoleSpec ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetSessionUserId () ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  InvalidOid ; 
#define  ROLESPEC_CSTRING 131 
#define  ROLESPEC_CURRENT_USER 130 
#define  ROLESPEC_PUBLIC 129 
#define  ROLESPEC_SESSION_USER 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  get_role_oid (int /*<<< orphan*/ ,int) ; 

Oid
get_rolespec_oid(const RoleSpec *role, bool missing_ok)
{
	Oid			oid;

	switch (role->roletype)
	{
		case ROLESPEC_CSTRING:
			Assert(role->rolename);
			oid = get_role_oid(role->rolename, missing_ok);
			break;

		case ROLESPEC_CURRENT_USER:
			oid = GetUserId();
			break;

		case ROLESPEC_SESSION_USER:
			oid = GetSessionUserId();
			break;

		case ROLESPEC_PUBLIC:
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("role \"%s\" does not exist", "public")));
			oid = InvalidOid;	/* make compiler happy */
			break;

		default:
			elog(ERROR, "unexpected role type %d", role->roletype);
	}

	return oid;
}