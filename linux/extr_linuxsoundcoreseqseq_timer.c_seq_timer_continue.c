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
struct snd_seq_timer {int running; int /*<<< orphan*/  last_update; int /*<<< orphan*/  ticks; int /*<<< orphan*/  timeri; int /*<<< orphan*/  initialized; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ initialize_timer (struct snd_seq_timer*) ; 
 int /*<<< orphan*/  ktime_get_ts64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_timer_reset (struct snd_seq_timer*) ; 
 int /*<<< orphan*/  snd_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int seq_timer_continue(struct snd_seq_timer *tmr)
{
	if (! tmr->timeri)
		return -EINVAL;
	if (tmr->running)
		return -EBUSY;
	if (! tmr->initialized) {
		seq_timer_reset(tmr);
		if (initialize_timer(tmr) < 0)
			return -EINVAL;
	}
	snd_timer_start(tmr->timeri, tmr->ticks);
	tmr->running = 1;
	ktime_get_ts64(&tmr->last_update);
	return 0;
}