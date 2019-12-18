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
struct snd_seq_timer {scalar_t__ running; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_seq_timer*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  snd_seq_timer_reset (struct snd_seq_timer*) ; 
 int /*<<< orphan*/  snd_seq_timer_stop (struct snd_seq_timer*) ; 

void snd_seq_timer_delete(struct snd_seq_timer **tmr)
{
	struct snd_seq_timer *t = *tmr;
	*tmr = NULL;

	if (t == NULL) {
		pr_debug("ALSA: seq: snd_seq_timer_delete() called with NULL timer\n");
		return;
	}
	t->running = 0;

	/* reset time */
	snd_seq_timer_stop(t);
	snd_seq_timer_reset(t);

	kfree(t);
}