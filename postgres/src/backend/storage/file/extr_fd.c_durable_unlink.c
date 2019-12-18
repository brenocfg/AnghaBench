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
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ fsync_parent_path (char const*,int) ; 
 scalar_t__ unlink (char const*) ; 

int
durable_unlink(const char *fname, int elevel)
{
	if (unlink(fname) < 0)
	{
		ereport(elevel,
				(errcode_for_file_access(),
				 errmsg("could not remove file \"%s\": %m",
						fname)));
		return -1;
	}

	/*
	 * To guarantee that the removal of the file is persistent, fsync its
	 * parent directory.
	 */
	if (fsync_parent_path(fname, elevel) != 0)
		return -1;

	return 0;
}