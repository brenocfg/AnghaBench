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
 int CHECKPOINT_CAUSE_TIME ; 
 int CHECKPOINT_CAUSE_XLOG ; 
 int CHECKPOINT_END_OF_RECOVERY ; 
 int CHECKPOINT_FLUSH_ALL ; 
 int CHECKPOINT_FORCE ; 
 int CHECKPOINT_IMMEDIATE ; 
 int CHECKPOINT_IS_SHUTDOWN ; 
 int CHECKPOINT_WAIT ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void
LogCheckpointStart(int flags, bool restartpoint)
{
	elog(LOG, "%s starting:%s%s%s%s%s%s%s%s",
		 restartpoint ? "restartpoint" : "checkpoint",
		 (flags & CHECKPOINT_IS_SHUTDOWN) ? " shutdown" : "",
		 (flags & CHECKPOINT_END_OF_RECOVERY) ? " end-of-recovery" : "",
		 (flags & CHECKPOINT_IMMEDIATE) ? " immediate" : "",
		 (flags & CHECKPOINT_FORCE) ? " force" : "",
		 (flags & CHECKPOINT_WAIT) ? " wait" : "",
		 (flags & CHECKPOINT_CAUSE_XLOG) ? " wal" : "",
		 (flags & CHECKPOINT_CAUSE_TIME) ? " time" : "",
		 (flags & CHECKPOINT_FLUSH_ALL) ? " flush-all" : "");
}