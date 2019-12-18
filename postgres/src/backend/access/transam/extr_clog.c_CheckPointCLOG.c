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
 int /*<<< orphan*/  ClogCtl ; 
 int /*<<< orphan*/  SimpleLruFlush (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_CLOG_CHECKPOINT_DONE (int) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_CLOG_CHECKPOINT_START (int) ; 
 int /*<<< orphan*/  fsync_fname (char*,int) ; 

void
CheckPointCLOG(void)
{
	/* Flush dirty CLOG pages to disk */
	TRACE_POSTGRESQL_CLOG_CHECKPOINT_START(true);
	SimpleLruFlush(ClogCtl, true);

	/*
	 * fsync pg_xact to ensure that any files flushed previously are durably
	 * on disk.
	 */
	fsync_fname("pg_xact", true);

	TRACE_POSTGRESQL_CLOG_CHECKPOINT_DONE(true);
}