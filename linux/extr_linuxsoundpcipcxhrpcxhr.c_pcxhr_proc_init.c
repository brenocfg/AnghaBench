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
struct snd_pcxhr {int /*<<< orphan*/  card; TYPE_1__* mgr; } ;
struct TYPE_5__ {int /*<<< orphan*/  write; } ;
struct TYPE_6__ {TYPE_2__ text; } ;
struct snd_info_entry {int mode; TYPE_3__ c; } ;
struct TYPE_4__ {scalar_t__ is_hr_stereo; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcxhr_proc_gpio_read ; 
 int /*<<< orphan*/  pcxhr_proc_gpo_write ; 
 int /*<<< orphan*/  pcxhr_proc_info ; 
 int /*<<< orphan*/  pcxhr_proc_ltc ; 
 int /*<<< orphan*/  pcxhr_proc_sync ; 
 int /*<<< orphan*/  snd_card_proc_new (int /*<<< orphan*/ ,char*,struct snd_info_entry**) ; 
 int /*<<< orphan*/  snd_info_set_text_ops (struct snd_info_entry*,struct snd_pcxhr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcxhr_proc_init(struct snd_pcxhr *chip)
{
	struct snd_info_entry *entry;

	if (! snd_card_proc_new(chip->card, "info", &entry))
		snd_info_set_text_ops(entry, chip, pcxhr_proc_info);
	if (! snd_card_proc_new(chip->card, "sync", &entry))
		snd_info_set_text_ops(entry, chip, pcxhr_proc_sync);
	/* gpio available on stereo sound cards only */
	if (chip->mgr->is_hr_stereo &&
	    !snd_card_proc_new(chip->card, "gpio", &entry)) {
		snd_info_set_text_ops(entry, chip, pcxhr_proc_gpio_read);
		entry->c.text.write = pcxhr_proc_gpo_write;
		entry->mode |= 0200;
	}
	if (!snd_card_proc_new(chip->card, "ltc", &entry))
		snd_info_set_text_ops(entry, chip, pcxhr_proc_ltc);
}