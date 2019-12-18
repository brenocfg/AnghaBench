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
struct snd_mixart {int /*<<< orphan*/  mgr; int /*<<< orphan*/  card; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct snd_info_entry {int /*<<< orphan*/  size; TYPE_1__ c; int /*<<< orphan*/  private_data; void* content; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIXART_BA0_SIZE ; 
 int /*<<< orphan*/  MIXART_BA1_SIZE ; 
 void* SNDRV_INFO_CONTENT_DATA ; 
 int /*<<< orphan*/  snd_card_proc_new (int /*<<< orphan*/ ,char*,struct snd_info_entry**) ; 
 int /*<<< orphan*/  snd_card_ro_proc_new (int /*<<< orphan*/ ,char*,struct snd_mixart*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mixart_proc_ops_BA0 ; 
 int /*<<< orphan*/  snd_mixart_proc_ops_BA1 ; 
 int /*<<< orphan*/  snd_mixart_proc_read ; 

__attribute__((used)) static void snd_mixart_proc_init(struct snd_mixart *chip)
{
	struct snd_info_entry *entry;

	/* text interface to read perf and temp meters */
	snd_card_ro_proc_new(chip->card, "board_info", chip,
			     snd_mixart_proc_read);

	if (! snd_card_proc_new(chip->card, "mixart_BA0", &entry)) {
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->private_data = chip->mgr;	
		entry->c.ops = &snd_mixart_proc_ops_BA0;
		entry->size = MIXART_BA0_SIZE;
	}
	if (! snd_card_proc_new(chip->card, "mixart_BA1", &entry)) {
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->private_data = chip->mgr;
		entry->c.ops = &snd_mixart_proc_ops_BA1;
		entry->size = MIXART_BA1_SIZE;
	}
}