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
struct TYPE_2__ {int /*<<< orphan*/  rolname; } ;
typedef  int /*<<< orphan*/  RoleSpec ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_authid ;

/* Variables and functions */
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rolespec_tuple (int /*<<< orphan*/  const*) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 

char *
get_rolespec_name(const RoleSpec *role)
{
	HeapTuple	tp;
	Form_pg_authid authForm;
	char	   *rolename;

	tp = get_rolespec_tuple(role);
	authForm = (Form_pg_authid) GETSTRUCT(tp);
	rolename = pstrdup(NameStr(authForm->rolname));
	ReleaseSysCache(tp);

	return rolename;
}