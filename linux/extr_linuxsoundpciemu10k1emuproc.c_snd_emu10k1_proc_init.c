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
struct TYPE_5__ {int /*<<< orphan*/  read; } ;
struct TYPE_6__ {TYPE_2__ text; int /*<<< orphan*/ * ops; } ;
struct snd_info_entry {int mode; TYPE_3__ c; struct snd_emu10k1* private_data; void* content; int /*<<< orphan*/  size; } ;
struct snd_emu10k1 {int /*<<< orphan*/  card; scalar_t__ audigy; TYPE_1__* card_capabilities; } ;
struct TYPE_4__ {scalar_t__ ca0151_chip; scalar_t__ emu10k2_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TOTAL_SIZE_CODE ; 
 int /*<<< orphan*/  A_TOTAL_SIZE_GPR ; 
 int /*<<< orphan*/  A_TOTAL_SIZE_TANKMEM_ADDR ; 
 int /*<<< orphan*/  A_TOTAL_SIZE_TANKMEM_DATA ; 
 void* SNDRV_INFO_CONTENT_DATA ; 
 void* SNDRV_INFO_CONTENT_TEXT ; 
 int S_IFREG ; 
 int /*<<< orphan*/  TOTAL_SIZE_CODE ; 
 int /*<<< orphan*/  TOTAL_SIZE_GPR ; 
 int /*<<< orphan*/  TOTAL_SIZE_TANKMEM_ADDR ; 
 int /*<<< orphan*/  TOTAL_SIZE_TANKMEM_DATA ; 
 int /*<<< orphan*/  snd_card_proc_new (int /*<<< orphan*/ ,char*,struct snd_info_entry**) ; 
 int /*<<< orphan*/  snd_emu10k1_proc_acode_read ; 
 int /*<<< orphan*/  snd_emu10k1_proc_ops_fx8010 ; 
 int /*<<< orphan*/  snd_emu10k1_proc_rates_read ; 
 int /*<<< orphan*/  snd_emu10k1_proc_read ; 
 int /*<<< orphan*/  snd_emu10k1_proc_spdif_read ; 
 int /*<<< orphan*/  snd_emu10k1_proc_voices_read ; 
 int /*<<< orphan*/  snd_info_set_text_ops (struct snd_info_entry*,struct snd_emu10k1*,int /*<<< orphan*/ ) ; 

int snd_emu10k1_proc_init(struct snd_emu10k1 *emu)
{
	struct snd_info_entry *entry;
#ifdef CONFIG_SND_DEBUG
	if (emu->card_capabilities->emu_model) {
		if (! snd_card_proc_new(emu->card, "emu1010_regs", &entry)) 
			snd_info_set_text_ops(entry, emu, snd_emu_proc_emu1010_reg_read);
	}
	if (! snd_card_proc_new(emu->card, "io_regs", &entry)) {
		snd_info_set_text_ops(entry, emu, snd_emu_proc_io_reg_read);
		entry->c.text.write = snd_emu_proc_io_reg_write;
		entry->mode |= 0200;
	}
	if (! snd_card_proc_new(emu->card, "ptr_regs00a", &entry)) {
		snd_info_set_text_ops(entry, emu, snd_emu_proc_ptr_reg_read00a);
		entry->c.text.write = snd_emu_proc_ptr_reg_write00;
		entry->mode |= 0200;
	}
	if (! snd_card_proc_new(emu->card, "ptr_regs00b", &entry)) {
		snd_info_set_text_ops(entry, emu, snd_emu_proc_ptr_reg_read00b);
		entry->c.text.write = snd_emu_proc_ptr_reg_write00;
		entry->mode |= 0200;
	}
	if (! snd_card_proc_new(emu->card, "ptr_regs20a", &entry)) {
		snd_info_set_text_ops(entry, emu, snd_emu_proc_ptr_reg_read20a);
		entry->c.text.write = snd_emu_proc_ptr_reg_write20;
		entry->mode |= 0200;
	}
	if (! snd_card_proc_new(emu->card, "ptr_regs20b", &entry)) {
		snd_info_set_text_ops(entry, emu, snd_emu_proc_ptr_reg_read20b);
		entry->c.text.write = snd_emu_proc_ptr_reg_write20;
		entry->mode |= 0200;
	}
	if (! snd_card_proc_new(emu->card, "ptr_regs20c", &entry)) {
		snd_info_set_text_ops(entry, emu, snd_emu_proc_ptr_reg_read20c);
		entry->c.text.write = snd_emu_proc_ptr_reg_write20;
		entry->mode |= 0200;
	}
#endif
	
	if (! snd_card_proc_new(emu->card, "emu10k1", &entry))
		snd_info_set_text_ops(entry, emu, snd_emu10k1_proc_read);

	if (emu->card_capabilities->emu10k2_chip) {
		if (! snd_card_proc_new(emu->card, "spdif-in", &entry))
			snd_info_set_text_ops(entry, emu, snd_emu10k1_proc_spdif_read);
	}
	if (emu->card_capabilities->ca0151_chip) {
		if (! snd_card_proc_new(emu->card, "capture-rates", &entry))
			snd_info_set_text_ops(entry, emu, snd_emu10k1_proc_rates_read);
	}

	if (! snd_card_proc_new(emu->card, "voices", &entry))
		snd_info_set_text_ops(entry, emu, snd_emu10k1_proc_voices_read);

	if (! snd_card_proc_new(emu->card, "fx8010_gpr", &entry)) {
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->private_data = emu;
		entry->mode = S_IFREG | 0444 /*| S_IWUSR*/;
		entry->size = emu->audigy ? A_TOTAL_SIZE_GPR : TOTAL_SIZE_GPR;
		entry->c.ops = &snd_emu10k1_proc_ops_fx8010;
	}
	if (! snd_card_proc_new(emu->card, "fx8010_tram_data", &entry)) {
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->private_data = emu;
		entry->mode = S_IFREG | 0444 /*| S_IWUSR*/;
		entry->size = emu->audigy ? A_TOTAL_SIZE_TANKMEM_DATA : TOTAL_SIZE_TANKMEM_DATA ;
		entry->c.ops = &snd_emu10k1_proc_ops_fx8010;
	}
	if (! snd_card_proc_new(emu->card, "fx8010_tram_addr", &entry)) {
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->private_data = emu;
		entry->mode = S_IFREG | 0444 /*| S_IWUSR*/;
		entry->size = emu->audigy ? A_TOTAL_SIZE_TANKMEM_ADDR : TOTAL_SIZE_TANKMEM_ADDR ;
		entry->c.ops = &snd_emu10k1_proc_ops_fx8010;
	}
	if (! snd_card_proc_new(emu->card, "fx8010_code", &entry)) {
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->private_data = emu;
		entry->mode = S_IFREG | 0444 /*| S_IWUSR*/;
		entry->size = emu->audigy ? A_TOTAL_SIZE_CODE : TOTAL_SIZE_CODE;
		entry->c.ops = &snd_emu10k1_proc_ops_fx8010;
	}
	if (! snd_card_proc_new(emu->card, "fx8010_acode", &entry)) {
		entry->content = SNDRV_INFO_CONTENT_TEXT;
		entry->private_data = emu;
		entry->mode = S_IFREG | 0444 /*| S_IWUSR*/;
		entry->c.text.read = snd_emu10k1_proc_acode_read;
	}
	return 0;
}