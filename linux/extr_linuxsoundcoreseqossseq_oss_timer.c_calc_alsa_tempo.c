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
struct seq_oss_timer {int tempo; int oss_tempo; int /*<<< orphan*/  oss_timebase; int /*<<< orphan*/  ppq; } ;

/* Variables and functions */

__attribute__((used)) static void
calc_alsa_tempo(struct seq_oss_timer *timer)
{
	timer->tempo = (60 * 1000000) / timer->oss_tempo;
	timer->ppq = timer->oss_timebase;
}