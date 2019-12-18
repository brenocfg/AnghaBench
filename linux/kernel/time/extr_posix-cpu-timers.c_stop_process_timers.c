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
struct posix_cputimers {int /*<<< orphan*/  timers_active; } ;
struct signal_struct {struct posix_cputimers posix_cputimers; } ;

/* Variables and functions */
 int /*<<< orphan*/  TICK_DEP_BIT_POSIX_TIMER ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tick_dep_clear_signal (struct signal_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void stop_process_timers(struct signal_struct *sig)
{
	struct posix_cputimers *pct = &sig->posix_cputimers;

	/* Turn off the active flag. This is done without locking. */
	WRITE_ONCE(pct->timers_active, false);
	tick_dep_clear_signal(sig, TICK_DEP_BIT_POSIX_TIMER);
}