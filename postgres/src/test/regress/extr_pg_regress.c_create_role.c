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
struct TYPE_3__ {int /*<<< orphan*/  str; struct TYPE_3__* next; } ;
typedef  TYPE_1__ _stringlist ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  header (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  psql_command (char*,char*,char const*,...) ; 

__attribute__((used)) static void
create_role(const char *rolename, const _stringlist *granted_dbs)
{
	header(_("creating role \"%s\""), rolename);
	psql_command("postgres", "CREATE ROLE \"%s\" WITH LOGIN", rolename);
	for (; granted_dbs != NULL; granted_dbs = granted_dbs->next)
	{
		psql_command("postgres", "GRANT ALL ON DATABASE \"%s\" TO \"%s\"",
					 granted_dbs->str, rolename);
	}
}