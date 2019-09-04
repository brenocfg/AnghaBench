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
struct TYPE_3__ {int /*<<< orphan*/  write; } ;
struct TYPE_4__ {TYPE_1__ text; } ;
struct snd_info_entry {int mode; struct snd_ca0106* private_data; TYPE_2__ c; } ;
struct snd_ca0106 {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ca0106_proc_i2c_write ; 
 int /*<<< orphan*/  snd_ca0106_proc_iec958 ; 
 int /*<<< orphan*/  snd_ca0106_proc_reg_read1 ; 
 int /*<<< orphan*/  snd_ca0106_proc_reg_read16 ; 
 int /*<<< orphan*/  snd_ca0106_proc_reg_read2 ; 
 int /*<<< orphan*/  snd_ca0106_proc_reg_read32 ; 
 int /*<<< orphan*/  snd_ca0106_proc_reg_read8 ; 
 int /*<<< orphan*/  snd_ca0106_proc_reg_write ; 
 int /*<<< orphan*/  snd_ca0106_proc_reg_write32 ; 
 int /*<<< orphan*/  snd_card_proc_new (int /*<<< orphan*/ ,char*,struct snd_info_entry**) ; 
 int /*<<< orphan*/  snd_info_set_text_ops (struct snd_info_entry*,struct snd_ca0106*,int /*<<< orphan*/ ) ; 

int snd_ca0106_proc_init(struct snd_ca0106 *emu)
{
	struct snd_info_entry *entry;
	
	if(! snd_card_proc_new(emu->card, "iec958", &entry))
		snd_info_set_text_ops(entry, emu, snd_ca0106_proc_iec958);
	if(! snd_card_proc_new(emu->card, "ca0106_reg32", &entry)) {
		snd_info_set_text_ops(entry, emu, snd_ca0106_proc_reg_read32);
		entry->c.text.write = snd_ca0106_proc_reg_write32;
		entry->mode |= 0200;
	}
	if(! snd_card_proc_new(emu->card, "ca0106_reg16", &entry))
		snd_info_set_text_ops(entry, emu, snd_ca0106_proc_reg_read16);
	if(! snd_card_proc_new(emu->card, "ca0106_reg8", &entry))
		snd_info_set_text_ops(entry, emu, snd_ca0106_proc_reg_read8);
	if(! snd_card_proc_new(emu->card, "ca0106_regs1", &entry)) {
		snd_info_set_text_ops(entry, emu, snd_ca0106_proc_reg_read1);
		entry->c.text.write = snd_ca0106_proc_reg_write;
		entry->mode |= 0200;
	}
	if(! snd_card_proc_new(emu->card, "ca0106_i2c", &entry)) {
		entry->c.text.write = snd_ca0106_proc_i2c_write;
		entry->private_data = emu;
		entry->mode |= 0200;
	}
	if(! snd_card_proc_new(emu->card, "ca0106_regs2", &entry)) 
		snd_info_set_text_ops(entry, emu, snd_ca0106_proc_reg_read2);
	return 0;
}