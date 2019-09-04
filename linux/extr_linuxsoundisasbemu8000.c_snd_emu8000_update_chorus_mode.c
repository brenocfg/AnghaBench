#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_emu8000 {int chorus_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  lfo_freq; int /*<<< orphan*/  delay; int /*<<< orphan*/  lfo_depth; int /*<<< orphan*/  delay_offset; int /*<<< orphan*/  feedback; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU8000_HWCF4_WRITE (struct snd_emu8000*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_HWCF5_WRITE (struct snd_emu8000*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_HWCF6_WRITE (struct snd_emu8000*,int) ; 
 int /*<<< orphan*/  EMU8000_HWCF7_WRITE (struct snd_emu8000*,int) ; 
 int /*<<< orphan*/  EMU8000_INIT3_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_INIT4_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int SNDRV_EMU8000_CHORUS_NUMBERS ; 
 int SNDRV_EMU8000_CHORUS_PREDEFINED ; 
 int /*<<< orphan*/ * chorus_defined ; 
 TYPE_1__* chorus_parm ; 

void
snd_emu8000_update_chorus_mode(struct snd_emu8000 *emu)
{
	int effect = emu->chorus_mode;
	if (effect < 0 || effect >= SNDRV_EMU8000_CHORUS_NUMBERS ||
	    (effect >= SNDRV_EMU8000_CHORUS_PREDEFINED && !chorus_defined[effect]))
		return;
	EMU8000_INIT3_WRITE(emu, 0x09, chorus_parm[effect].feedback);
	EMU8000_INIT3_WRITE(emu, 0x0c, chorus_parm[effect].delay_offset);
	EMU8000_INIT4_WRITE(emu, 0x03, chorus_parm[effect].lfo_depth);
	EMU8000_HWCF4_WRITE(emu, chorus_parm[effect].delay);
	EMU8000_HWCF5_WRITE(emu, chorus_parm[effect].lfo_freq);
	EMU8000_HWCF6_WRITE(emu, 0x8000);
	EMU8000_HWCF7_WRITE(emu, 0x0000);
}