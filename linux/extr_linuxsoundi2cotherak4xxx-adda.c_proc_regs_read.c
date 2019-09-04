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
struct snd_info_entry {struct snd_akm4xxx* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct snd_akm4xxx {int num_chips; int total_regs; } ;

/* Variables and functions */
 int snd_akm4xxx_get (struct snd_akm4xxx*,int,int) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,int,int,int) ; 

__attribute__((used)) static void proc_regs_read(struct snd_info_entry *entry,
		struct snd_info_buffer *buffer)
{
	struct snd_akm4xxx *ak = entry->private_data;
	int reg, val, chip;
	for (chip = 0; chip < ak->num_chips; chip++) {
		for (reg = 0; reg < ak->total_regs; reg++) {
			val =  snd_akm4xxx_get(ak, chip, reg);
			snd_iprintf(buffer, "chip %d: 0x%02x = 0x%02x\n", chip,
					reg, val);
		}
	}
}