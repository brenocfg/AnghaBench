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
struct snd_pcxhr {int /*<<< orphan*/  card; TYPE_1__* mgr; } ;
struct TYPE_2__ {scalar_t__ is_hr_stereo; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcxhr_proc_gpio_read ; 
 int /*<<< orphan*/  pcxhr_proc_gpo_write ; 
 int /*<<< orphan*/  pcxhr_proc_info ; 
 int /*<<< orphan*/  pcxhr_proc_ltc ; 
 int /*<<< orphan*/  pcxhr_proc_sync ; 
 int /*<<< orphan*/  snd_card_ro_proc_new (int /*<<< orphan*/ ,char*,struct snd_pcxhr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_card_rw_proc_new (int /*<<< orphan*/ ,char*,struct snd_pcxhr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcxhr_proc_init(struct snd_pcxhr *chip)
{
	snd_card_ro_proc_new(chip->card, "info", chip, pcxhr_proc_info);
	snd_card_ro_proc_new(chip->card, "sync", chip, pcxhr_proc_sync);
	/* gpio available on stereo sound cards only */
	if (chip->mgr->is_hr_stereo)
		snd_card_rw_proc_new(chip->card, "gpio", chip,
				     pcxhr_proc_gpio_read,
				     pcxhr_proc_gpo_write);
	snd_card_ro_proc_new(chip->card, "ltc", chip, pcxhr_proc_ltc);
}