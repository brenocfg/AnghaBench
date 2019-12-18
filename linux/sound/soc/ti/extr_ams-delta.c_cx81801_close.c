#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {struct snd_soc_component* disc_data; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {TYPE_1__* card; } ;
struct TYPE_6__ {int /*<<< orphan*/  pins; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* close ) (struct tty_struct*) ;} ;
struct TYPE_4__ {struct snd_soc_dapm_context dapm; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_3__ ams_delta_hook_switch ; 
 int /*<<< orphan*/  cx81801_timer ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin_unlocked (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin_unlocked (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_lock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_unlock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync_unlocked (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 TYPE_2__ v253_ops ; 

__attribute__((used)) static void cx81801_close(struct tty_struct *tty)
{
	struct snd_soc_component *component = tty->disc_data;
	struct snd_soc_dapm_context *dapm = &component->card->dapm;

	del_timer_sync(&cx81801_timer);

	/* Prevent the hook switch from further changing the DAPM pins */
	INIT_LIST_HEAD(&ams_delta_hook_switch.pins);

	if (!component)
		return;

	v253_ops.close(tty);

	/* Revert back to default audio input/output constellation */
	snd_soc_dapm_mutex_lock(dapm);

	snd_soc_dapm_disable_pin_unlocked(dapm, "Mouthpiece");
	snd_soc_dapm_enable_pin_unlocked(dapm, "Earpiece");
	snd_soc_dapm_enable_pin_unlocked(dapm, "Microphone");
	snd_soc_dapm_disable_pin_unlocked(dapm, "Speaker");
	snd_soc_dapm_disable_pin_unlocked(dapm, "AGCIN");

	snd_soc_dapm_sync_unlocked(dapm);

	snd_soc_dapm_mutex_unlock(dapm);
}