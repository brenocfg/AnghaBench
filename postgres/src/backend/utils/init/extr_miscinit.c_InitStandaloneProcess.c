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
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  InitLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitProcessGlobals () ; 
 int /*<<< orphan*/  InitializeLatchSupport () ; 
 int /*<<< orphan*/  IsPostmasterEnvironment ; 
 int /*<<< orphan*/  LocalLatchData ; 
 int /*<<< orphan*/ * MyLatch ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ find_my_exec (char const*,char*) ; 
 int /*<<< orphan*/  get_pkglib_path (char*,char*) ; 
 char* my_exec_path ; 
 char* pkglib_path ; 

void
InitStandaloneProcess(const char *argv0)
{
	Assert(!IsPostmasterEnvironment);

	InitProcessGlobals();

	/* Initialize process-local latch support */
	InitializeLatchSupport();
	MyLatch = &LocalLatchData;
	InitLatch(MyLatch);

	/* Compute paths, no postmaster to inherit from */
	if (my_exec_path[0] == '\0')
	{
		if (find_my_exec(argv0, my_exec_path) < 0)
			elog(FATAL, "%s: could not locate my own executable path",
				 argv0);
	}

	if (pkglib_path[0] == '\0')
		get_pkglib_path(my_exec_path, pkglib_path);
}