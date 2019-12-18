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
struct TYPE_3__ {int roletype; char* rolename; } ;
typedef  TYPE_1__ RoleSpec ;
typedef  int /*<<< orphan*/ * HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHNAME ; 
 int /*<<< orphan*/  AUTHOID ; 
 int /*<<< orphan*/  Assert (char*) ; 
 int CStringGetDatum (char*) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int GetSessionUserId () ; 
 int GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ *) ; 
#define  ROLESPEC_CSTRING 131 
#define  ROLESPEC_CURRENT_USER 130 
#define  ROLESPEC_PUBLIC 129 
#define  ROLESPEC_SESSION_USER 128 
 int /*<<< orphan*/ * SearchSysCache1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 

HeapTuple
get_rolespec_tuple(const RoleSpec *role)
{
	HeapTuple	tuple;

	switch (role->roletype)
	{
		case ROLESPEC_CSTRING:
			Assert(role->rolename);
			tuple = SearchSysCache1(AUTHNAME, CStringGetDatum(role->rolename));
			if (!HeapTupleIsValid(tuple))
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_OBJECT),
						 errmsg("role \"%s\" does not exist", role->rolename)));
			break;

		case ROLESPEC_CURRENT_USER:
			tuple = SearchSysCache1(AUTHOID, GetUserId());
			if (!HeapTupleIsValid(tuple))
				elog(ERROR, "cache lookup failed for role %u", GetUserId());
			break;

		case ROLESPEC_SESSION_USER:
			tuple = SearchSysCache1(AUTHOID, GetSessionUserId());
			if (!HeapTupleIsValid(tuple))
				elog(ERROR, "cache lookup failed for role %u", GetSessionUserId());
			break;

		case ROLESPEC_PUBLIC:
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("role \"%s\" does not exist", "public")));
			tuple = NULL;		/* make compiler happy */
			break;

		default:
			elog(ERROR, "unexpected role type %d", role->roletype);
	}

	return tuple;
}