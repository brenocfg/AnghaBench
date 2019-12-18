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
struct snd_info_entry {struct ak4113* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct ak4113 {int dummy; } ;

/* Variables and functions */
 int reg_read (struct ak4113*,int) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,int,int) ; 

__attribute__((used)) static void snd_ak4113_proc_regs_read(struct snd_info_entry *entry,
		struct snd_info_buffer *buffer)
{
	struct ak4113 *ak4113 = entry->private_data;
	int reg, val;
	/* all ak4113 registers 0x00 - 0x1c */
	for (reg = 0; reg < 0x1d; reg++) {
		val = reg_read(ak4113, reg);
		snd_iprintf(buffer, "0x%02x = 0x%02x\n", reg, val);
	}
}