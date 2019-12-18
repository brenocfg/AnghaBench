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
 int /*<<< orphan*/  AssertState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DataDir ; 
 int /*<<< orphan*/  FATAL ; 
 scalar_t__ chdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

void
ChangeToDataDir(void)
{
	AssertState(DataDir);

	if (chdir(DataDir) < 0)
		ereport(FATAL,
				(errcode_for_file_access(),
				 errmsg("could not change directory to \"%s\": %m",
						DataDir)));
}