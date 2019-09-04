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
struct snd_info_entry {struct snd_ca0106* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct snd_ca0106 {int /*<<< orphan*/  emu_lock; scalar_t__ port; } ;

/* Variables and functions */
 unsigned int inb (scalar_t__) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_ca0106_proc_reg_read8(struct snd_info_entry *entry, 
				       struct snd_info_buffer *buffer)
{
	struct snd_ca0106 *emu = entry->private_data;
	unsigned int value;
	unsigned long flags;
	int i;
	snd_iprintf(buffer, "Registers:\n\n");
	for(i = 0; i < 0x20; i+=1) {
		spin_lock_irqsave(&emu->emu_lock, flags);
		value = inb(emu->port + i);
		spin_unlock_irqrestore(&emu->emu_lock, flags);
		snd_iprintf(buffer, "Register %02X: %02X\n", i, value);
	}
}