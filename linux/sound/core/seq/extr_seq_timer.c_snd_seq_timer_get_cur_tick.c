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
struct TYPE_2__ {int /*<<< orphan*/  cur_tick; } ;
struct snd_seq_timer {TYPE_1__ tick; } ;
typedef  int /*<<< orphan*/  snd_seq_tick_time_t ;

/* Variables and functions */

snd_seq_tick_time_t snd_seq_timer_get_cur_tick(struct snd_seq_timer *tmr)
{
	return tmr->tick.cur_tick;
}