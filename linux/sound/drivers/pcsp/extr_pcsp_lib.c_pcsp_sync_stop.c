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
struct snd_pcsp {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  pcsp_pcm_tasklet ; 
 int /*<<< orphan*/  pcsp_stop_playing (struct snd_pcsp*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void pcsp_sync_stop(struct snd_pcsp *chip)
{
	local_irq_disable();
	pcsp_stop_playing(chip);
	local_irq_enable();
	hrtimer_cancel(&chip->timer);
	tasklet_kill(&pcsp_pcm_tasklet);
}