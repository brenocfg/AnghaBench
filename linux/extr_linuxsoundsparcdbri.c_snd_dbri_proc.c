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
struct snd_info_entry {int dummy; } ;
struct snd_dbri {int dummy; } ;
struct snd_card {struct snd_dbri* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbri_regs_read ; 
 int /*<<< orphan*/  snd_card_proc_new (struct snd_card*,char*,struct snd_info_entry**) ; 
 int /*<<< orphan*/  snd_info_set_text_ops (struct snd_info_entry*,struct snd_dbri*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_dbri_proc(struct snd_card *card)
{
	struct snd_dbri *dbri = card->private_data;
	struct snd_info_entry *entry;

	if (!snd_card_proc_new(card, "regs", &entry))
		snd_info_set_text_ops(entry, dbri, dbri_regs_read);

#ifdef DBRI_DEBUG
	if (!snd_card_proc_new(card, "debug", &entry)) {
		snd_info_set_text_ops(entry, dbri, dbri_debug_read);
		entry->mode = S_IFREG | 0444;	/* Readable only. */
	}
#endif
}