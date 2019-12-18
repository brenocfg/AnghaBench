#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_opl4 {scalar_t__ hardware; struct snd_info_entry* proc_entry; TYPE_2__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ops; } ;
struct snd_info_entry {int mode; int size; struct snd_opl4* private_data; int /*<<< orphan*/  module; TYPE_1__ c; int /*<<< orphan*/  content; } ;
struct TYPE_4__ {int /*<<< orphan*/  proc_root; } ;

/* Variables and functions */
 scalar_t__ OPL3_HW_OPL4_ML ; 
 int /*<<< orphan*/  SNDRV_INFO_CONTENT_DATA ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct snd_info_entry* snd_info_create_card_entry (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_opl4_mem_proc_ops ; 

int snd_opl4_create_proc(struct snd_opl4 *opl4)
{
	struct snd_info_entry *entry;

	entry = snd_info_create_card_entry(opl4->card, "opl4-mem", opl4->card->proc_root);
	if (entry) {
		if (opl4->hardware < OPL3_HW_OPL4_ML) {
			/* OPL4 can access 4 MB external ROM/SRAM */
			entry->mode |= 0200;
			entry->size = 4 * 1024 * 1024;
		} else {
			/* OPL4-ML has 1 MB internal ROM */
			entry->size = 1 * 1024 * 1024;
		}
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->c.ops = &snd_opl4_mem_proc_ops;
		entry->module = THIS_MODULE;
		entry->private_data = opl4;
	}
	opl4->proc_entry = entry;
	return 0;
}