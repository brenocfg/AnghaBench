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
struct snd_ac97 {size_t num; int /*<<< orphan*/  (* private_free ) (struct snd_ac97*) ;TYPE_1__* bus; int /*<<< orphan*/  power_work; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_ac97*) ; 
 int /*<<< orphan*/  snd_ac97_proc_done (struct snd_ac97*) ; 
 int /*<<< orphan*/  stub1 (struct snd_ac97*) ; 

__attribute__((used)) static int snd_ac97_free(struct snd_ac97 *ac97)
{
	if (ac97) {
#ifdef CONFIG_SND_AC97_POWER_SAVE
		cancel_delayed_work_sync(&ac97->power_work);
#endif
		snd_ac97_proc_done(ac97);
		if (ac97->bus)
			ac97->bus->codec[ac97->num] = NULL;
		if (ac97->private_free)
			ac97->private_free(ac97);
		kfree(ac97);
	}
	return 0;
}