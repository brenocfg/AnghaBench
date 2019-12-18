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
struct snd_seq_timer {int /*<<< orphan*/  timeri; scalar_t__ running; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  snd_timer_pause (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int seq_timer_stop(struct snd_seq_timer *tmr)
{
	if (! tmr->timeri)
		return -EINVAL;
	if (!tmr->running)
		return 0;
	tmr->running = 0;
	snd_timer_pause(tmr->timeri);
	return 0;
}