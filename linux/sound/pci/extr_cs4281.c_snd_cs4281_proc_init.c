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
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct snd_info_entry {int /*<<< orphan*/  size; TYPE_1__ c; struct cs4281* private_data; void* content; } ;
struct cs4281 {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4281_BA0_SIZE ; 
 int /*<<< orphan*/  CS4281_BA1_SIZE ; 
 void* SNDRV_INFO_CONTENT_DATA ; 
 int /*<<< orphan*/  snd_card_proc_new (int /*<<< orphan*/ ,char*,struct snd_info_entry**) ; 
 int /*<<< orphan*/  snd_card_ro_proc_new (int /*<<< orphan*/ ,char*,struct cs4281*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs4281_proc_ops_BA0 ; 
 int /*<<< orphan*/  snd_cs4281_proc_ops_BA1 ; 
 int /*<<< orphan*/  snd_cs4281_proc_read ; 

__attribute__((used)) static void snd_cs4281_proc_init(struct cs4281 *chip)
{
	struct snd_info_entry *entry;

	snd_card_ro_proc_new(chip->card, "cs4281", chip, snd_cs4281_proc_read);
	if (! snd_card_proc_new(chip->card, "cs4281_BA0", &entry)) {
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->private_data = chip;
		entry->c.ops = &snd_cs4281_proc_ops_BA0;
		entry->size = CS4281_BA0_SIZE;
	}
	if (! snd_card_proc_new(chip->card, "cs4281_BA1", &entry)) {
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->private_data = chip;
		entry->c.ops = &snd_cs4281_proc_ops_BA1;
		entry->size = CS4281_BA1_SIZE;
	}
}