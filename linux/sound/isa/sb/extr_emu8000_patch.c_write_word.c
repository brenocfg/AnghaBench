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
struct snd_emu8000 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU8000_SMALW_WRITE (struct snd_emu8000*,int) ; 
 int /*<<< orphan*/  EMU8000_SMLD_WRITE (struct snd_emu8000*,unsigned short) ; 
 int emu8000_reset_addr ; 
 int /*<<< orphan*/  snd_emu8000_write_wait (struct snd_emu8000*) ; 

__attribute__((used)) static inline void
write_word(struct snd_emu8000 *emu, int *offset, unsigned short data)
{
	if (emu8000_reset_addr) {
		if (emu8000_reset_addr > 1)
			snd_emu8000_write_wait(emu);
		EMU8000_SMALW_WRITE(emu, *offset);
	}
	EMU8000_SMLD_WRITE(emu, data);
	*offset += 1;
}