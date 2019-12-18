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
struct TYPE_3__ {int /*<<< orphan*/  read; } ;
struct TYPE_4__ {TYPE_1__ text; } ;
struct snd_info_entry {TYPE_2__ c; struct snd_emux* private_data; int /*<<< orphan*/  content; } ;
struct snd_emux {int dummy; } ;
struct snd_card {int /*<<< orphan*/  proc_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_INFO_CONTENT_TEXT ; 
 int /*<<< orphan*/  snd_emux_proc_info_read ; 
 struct snd_info_entry* snd_info_create_card_entry (struct snd_card*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void snd_emux_proc_init(struct snd_emux *emu, struct snd_card *card, int device)
{
	struct snd_info_entry *entry;
	char name[64];

	sprintf(name, "wavetableD%d", device);
	entry = snd_info_create_card_entry(card, name, card->proc_root);
	if (entry == NULL)
		return;

	entry->content = SNDRV_INFO_CONTENT_TEXT;
	entry->private_data = emu;
	entry->c.text.read = snd_emux_proc_info_read;
}