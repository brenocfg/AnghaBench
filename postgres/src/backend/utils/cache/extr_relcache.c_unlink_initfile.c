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
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ errno ; 
 scalar_t__ unlink (char const*) ; 

__attribute__((used)) static void
unlink_initfile(const char *initfilename, int elevel)
{
	if (unlink(initfilename) < 0)
	{
		/* It might not be there, but log any error other than ENOENT */
		if (errno != ENOENT)
			ereport(elevel,
					(errcode_for_file_access(),
					 errmsg("could not remove cache file \"%s\": %m",
							initfilename)));
	}
}