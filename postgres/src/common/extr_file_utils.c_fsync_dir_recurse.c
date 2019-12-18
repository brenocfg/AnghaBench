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
 int /*<<< orphan*/  fsync_fname ; 
 int /*<<< orphan*/  pre_sync_fname ; 
 int /*<<< orphan*/  walkdir (char const*,int /*<<< orphan*/ ,int) ; 

void
fsync_dir_recurse(const char *dir)
{
	/*
	 * If possible, hint to the kernel that we're soon going to fsync the data
	 * directory and its contents.
	 */
#ifdef PG_FLUSH_DATA_WORKS
	walkdir(dir, pre_sync_fname, false);
#endif

	walkdir(dir, fsync_fname, false);
}