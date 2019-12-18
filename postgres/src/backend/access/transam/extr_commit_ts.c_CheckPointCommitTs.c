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
 int /*<<< orphan*/  CommitTsCtl ; 
 int /*<<< orphan*/  SimpleLruFlush (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fsync_fname (char*,int) ; 

void
CheckPointCommitTs(void)
{
	/* Flush dirty CommitTs pages to disk */
	SimpleLruFlush(CommitTsCtl, true);

	/*
	 * fsync pg_commit_ts to ensure that any files flushed previously are
	 * durably on disk.
	 */
	fsync_fname("pg_commit_ts", true);
}