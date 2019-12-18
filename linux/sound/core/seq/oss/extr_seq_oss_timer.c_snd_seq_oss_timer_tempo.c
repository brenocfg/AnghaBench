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
struct seq_oss_timer {int oss_tempo; int /*<<< orphan*/  tempo; int /*<<< orphan*/  dp; scalar_t__ running; } ;

/* Variables and functions */
 int MAX_OSS_TEMPO ; 
 int MIN_OSS_TEMPO ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_TEMPO ; 
 int /*<<< orphan*/  calc_alsa_tempo (struct seq_oss_timer*) ; 
 int /*<<< orphan*/  send_timer_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
snd_seq_oss_timer_tempo(struct seq_oss_timer *timer, int value)
{
	if (value < MIN_OSS_TEMPO)
		value = MIN_OSS_TEMPO;
	else if (value > MAX_OSS_TEMPO)
		value = MAX_OSS_TEMPO;
	timer->oss_tempo = value;
	calc_alsa_tempo(timer);
	if (timer->running)
		send_timer_event(timer->dp, SNDRV_SEQ_EVENT_TEMPO, timer->tempo);
	return 0;
}