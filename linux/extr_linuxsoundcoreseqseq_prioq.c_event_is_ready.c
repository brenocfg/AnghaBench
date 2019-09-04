#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  time; int /*<<< orphan*/  tick; } ;
struct snd_seq_event {int flags; TYPE_1__ time; } ;

/* Variables and functions */
 int SNDRV_SEQ_TIME_STAMP_MASK ; 
 int SNDRV_SEQ_TIME_STAMP_TICK ; 
 int snd_seq_compare_real_time (void*,int /*<<< orphan*/ *) ; 
 int snd_seq_compare_tick_time (void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int event_is_ready(struct snd_seq_event *ev, void *current_time)
{
	if ((ev->flags & SNDRV_SEQ_TIME_STAMP_MASK) == SNDRV_SEQ_TIME_STAMP_TICK)
		return snd_seq_compare_tick_time(current_time, &ev->time.tick);
	else
		return snd_seq_compare_real_time(current_time, &ev->time.time);
}