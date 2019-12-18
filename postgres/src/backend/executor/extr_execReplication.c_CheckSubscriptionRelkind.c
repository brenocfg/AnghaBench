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

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 char RELKIND_FOREIGN_TABLE ; 
 char RELKIND_PARTITIONED_TABLE ; 
 char RELKIND_RELATION ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char const*,char const*) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,char const*) ; 

void
CheckSubscriptionRelkind(char relkind, const char *nspname,
						 const char *relname)
{
	/*
	 * We currently only support writing to regular tables.  However, give a
	 * more specific error for partitioned and foreign tables.
	 */
	if (relkind == RELKIND_PARTITIONED_TABLE)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot use relation \"%s.%s\" as logical replication target",
						nspname, relname),
				 errdetail("\"%s.%s\" is a partitioned table.",
						   nspname, relname)));
	else if (relkind == RELKIND_FOREIGN_TABLE)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot use relation \"%s.%s\" as logical replication target",
						nspname, relname),
				 errdetail("\"%s.%s\" is a foreign table.",
						   nspname, relname)));

	if (relkind != RELKIND_RELATION)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot use relation \"%s.%s\" as logical replication target",
						nspname, relname),
				 errdetail("\"%s.%s\" is not a table.",
						   nspname, relname)));
}