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
struct snd_info_entry {struct emu10k1x* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct emu10k1x {int /*<<< orphan*/  emu_lock; scalar_t__ port; } ;

/* Variables and functions */
 unsigned long inl (scalar_t__) ; 
 unsigned long snd_emu10k1x_ptr_read (struct emu10k1x*,int,int) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_emu10k1x_proc_reg_read(struct snd_info_entry *entry, 
				       struct snd_info_buffer *buffer)
{
	struct emu10k1x *emu = entry->private_data;
	unsigned long value,value1,value2;
	unsigned long flags;
	int i;

	snd_iprintf(buffer, "Registers:\n\n");
	for(i = 0; i < 0x20; i+=4) {
		spin_lock_irqsave(&emu->emu_lock, flags);
		value = inl(emu->port + i);
		spin_unlock_irqrestore(&emu->emu_lock, flags);
		snd_iprintf(buffer, "Register %02X: %08lX\n", i, value);
	}
	snd_iprintf(buffer, "\nRegisters\n\n");
	for(i = 0; i <= 0x48; i++) {
		value = snd_emu10k1x_ptr_read(emu, i, 0);
		if(i < 0x10 || (i >= 0x20 && i < 0x40)) {
			value1 = snd_emu10k1x_ptr_read(emu, i, 1);
			value2 = snd_emu10k1x_ptr_read(emu, i, 2);
			snd_iprintf(buffer, "%02X: %08lX %08lX %08lX\n", i, value, value1, value2);
		} else {
			snd_iprintf(buffer, "%02X: %08lX\n", i, value);
		}
	}
}