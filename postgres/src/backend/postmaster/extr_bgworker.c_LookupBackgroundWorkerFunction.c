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
typedef  int /*<<< orphan*/  bgworker_main_type ;
struct TYPE_3__ {char const* fn_name; int /*<<< orphan*/  fn_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* InternalBGWorkers ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*) ; 
 int lengthof (TYPE_1__*) ; 
 int /*<<< orphan*/  load_external_function (char const*,char const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static bgworker_main_type
LookupBackgroundWorkerFunction(const char *libraryname, const char *funcname)
{
	/*
	 * If the function is to be loaded from postgres itself, search the
	 * InternalBGWorkers array.
	 */
	if (strcmp(libraryname, "postgres") == 0)
	{
		int			i;

		for (i = 0; i < lengthof(InternalBGWorkers); i++)
		{
			if (strcmp(InternalBGWorkers[i].fn_name, funcname) == 0)
				return InternalBGWorkers[i].fn_addr;
		}

		/* We can only reach this by programming error. */
		elog(ERROR, "internal function \"%s\" not found", funcname);
	}

	/* Otherwise load from external library. */
	return (bgworker_main_type)
		load_external_function(libraryname, funcname, true, NULL);
}