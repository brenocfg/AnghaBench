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
struct jfs_log {int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_LOCK (struct jfs_log*) ; 
 int /*<<< orphan*/  LOG_UNLOCK (struct jfs_log*) ; 
 int /*<<< orphan*/  lmLogSync (struct jfs_log*,int) ; 
 int /*<<< orphan*/  log_QUIESCE ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void jfs_syncpt(struct jfs_log *log, int hard_sync)
{	LOG_LOCK(log);
	if (!test_bit(log_QUIESCE, &log->flag))
		lmLogSync(log, hard_sync);
	LOG_UNLOCK(log);
}