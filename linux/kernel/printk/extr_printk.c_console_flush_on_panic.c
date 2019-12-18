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
typedef  enum con_flush_mode { ____Placeholder_con_flush_mode } con_flush_mode ;

/* Variables and functions */
 int CONSOLE_REPLAY_ALL ; 
 int /*<<< orphan*/  console_idx ; 
 scalar_t__ console_may_schedule ; 
 int /*<<< orphan*/  console_seq ; 
 int /*<<< orphan*/  console_trylock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  log_first_idx ; 
 int /*<<< orphan*/  log_first_seq ; 
 int /*<<< orphan*/  logbuf_lock_irqsave (unsigned long) ; 
 int /*<<< orphan*/  logbuf_unlock_irqrestore (unsigned long) ; 

void console_flush_on_panic(enum con_flush_mode mode)
{
	/*
	 * If someone else is holding the console lock, trylock will fail
	 * and may_schedule may be set.  Ignore and proceed to unlock so
	 * that messages are flushed out.  As this can be called from any
	 * context and we don't want to get preempted while flushing,
	 * ensure may_schedule is cleared.
	 */
	console_trylock();
	console_may_schedule = 0;

	if (mode == CONSOLE_REPLAY_ALL) {
		unsigned long flags;

		logbuf_lock_irqsave(flags);
		console_seq = log_first_seq;
		console_idx = log_first_idx;
		logbuf_unlock_irqrestore(flags);
	}
	console_unlock();
}