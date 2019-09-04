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
struct cmipci {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_card_proc_new (int /*<<< orphan*/ ,char*,struct snd_info_entry**) ; 
 int /*<<< orphan*/  snd_cmipci_proc_read ; 
 int /*<<< orphan*/  snd_info_set_text_ops (struct snd_info_entry*,struct cmipci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_cmipci_proc_init(struct cmipci *cm)
{
	struct snd_info_entry *entry;

	if (! snd_card_proc_new(cm->card, "cmipci", &entry))
		snd_info_set_text_ops(entry, cm, snd_cmipci_proc_read);
}