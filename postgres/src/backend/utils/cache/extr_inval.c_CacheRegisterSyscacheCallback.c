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
struct TYPE_2__ {int link; int id; int /*<<< orphan*/  arg; int /*<<< orphan*/  function; } ;
typedef  int /*<<< orphan*/  SyscacheCallbackFunction ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL ; 
 int MAX_SYSCACHE_CALLBACKS ; 
 int SysCacheSize ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int syscache_callback_count ; 
 int* syscache_callback_links ; 
 TYPE_1__* syscache_callback_list ; 

void
CacheRegisterSyscacheCallback(int cacheid,
							  SyscacheCallbackFunction func,
							  Datum arg)
{
	if (cacheid < 0 || cacheid >= SysCacheSize)
		elog(FATAL, "invalid cache ID: %d", cacheid);
	if (syscache_callback_count >= MAX_SYSCACHE_CALLBACKS)
		elog(FATAL, "out of syscache_callback_list slots");

	if (syscache_callback_links[cacheid] == 0)
	{
		/* first callback for this cache */
		syscache_callback_links[cacheid] = syscache_callback_count + 1;
	}
	else
	{
		/* add to end of chain, so that older callbacks are called first */
		int			i = syscache_callback_links[cacheid] - 1;

		while (syscache_callback_list[i].link > 0)
			i = syscache_callback_list[i].link - 1;
		syscache_callback_list[i].link = syscache_callback_count + 1;
	}

	syscache_callback_list[syscache_callback_count].id = cacheid;
	syscache_callback_list[syscache_callback_count].link = 0;
	syscache_callback_list[syscache_callback_count].function = func;
	syscache_callback_list[syscache_callback_count].arg = arg;

	++syscache_callback_count;
}