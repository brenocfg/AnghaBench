#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * head; } ;
struct TYPE_4__ {TYPE_2__ triggerNames; TYPE_2__ functionNames; TYPE_2__ indexNames; TYPE_2__ tableNames; TYPE_2__ schemaNames; int /*<<< orphan*/  strict_names; } ;
typedef  TYPE_1__ RestoreOptions ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 char* simple_string_list_not_touched (TYPE_2__*) ; 

__attribute__((used)) static void
StrictNamesCheck(RestoreOptions *ropt)
{
	const char *missing_name;

	Assert(ropt->strict_names);

	if (ropt->schemaNames.head != NULL)
	{
		missing_name = simple_string_list_not_touched(&ropt->schemaNames);
		if (missing_name != NULL)
			fatal("schema \"%s\" not found", missing_name);
	}

	if (ropt->tableNames.head != NULL)
	{
		missing_name = simple_string_list_not_touched(&ropt->tableNames);
		if (missing_name != NULL)
			fatal("table \"%s\" not found", missing_name);
	}

	if (ropt->indexNames.head != NULL)
	{
		missing_name = simple_string_list_not_touched(&ropt->indexNames);
		if (missing_name != NULL)
			fatal("index \"%s\" not found", missing_name);
	}

	if (ropt->functionNames.head != NULL)
	{
		missing_name = simple_string_list_not_touched(&ropt->functionNames);
		if (missing_name != NULL)
			fatal("function \"%s\" not found", missing_name);
	}

	if (ropt->triggerNames.head != NULL)
	{
		missing_name = simple_string_list_not_touched(&ropt->triggerNames);
		if (missing_name != NULL)
			fatal("trigger \"%s\" not found", missing_name);
	}
}