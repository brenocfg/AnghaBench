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
 int /*<<< orphan*/  DEBUG4 ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NoLock ; 
 char* RelationGetRelationName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * boot_reldesc ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
closerel(char *name)
{
	if (name)
	{
		if (boot_reldesc)
		{
			if (strcmp(RelationGetRelationName(boot_reldesc), name) != 0)
				elog(ERROR, "close of %s when %s was expected",
					 name, RelationGetRelationName(boot_reldesc));
		}
		else
			elog(ERROR, "close of %s before any relation was opened",
				 name);
	}

	if (boot_reldesc == NULL)
		elog(ERROR, "no open relation to close");
	else
	{
		elog(DEBUG4, "close relation %s",
			 RelationGetRelationName(boot_reldesc));
		table_close(boot_reldesc, NoLock);
		boot_reldesc = NULL;
	}
}