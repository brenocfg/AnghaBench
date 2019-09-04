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
struct snd_akm4xxx {int /*<<< orphan*/  name; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_regs_read ; 
 int snd_card_proc_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_info_entry**) ; 
 int /*<<< orphan*/  snd_info_set_text_ops (struct snd_info_entry*,struct snd_akm4xxx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_init(struct snd_akm4xxx *ak)
{
	struct snd_info_entry *entry;
	int err;
	err = snd_card_proc_new(ak->card, ak->name, &entry);
	if (err < 0)
		return err;
	snd_info_set_text_ops(entry, ak, proc_regs_read);
	return 0;
}