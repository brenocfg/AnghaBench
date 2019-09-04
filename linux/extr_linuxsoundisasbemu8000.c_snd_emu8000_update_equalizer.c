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
struct snd_emu8000 {int bass_level; int treble_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU8000_INIT3_WRITE (struct snd_emu8000*,int,unsigned short) ; 
 int /*<<< orphan*/  EMU8000_INIT4_WRITE (struct snd_emu8000*,int,unsigned short) ; 
 unsigned short** bass_parm ; 
 unsigned short** treble_parm ; 

void
snd_emu8000_update_equalizer(struct snd_emu8000 *emu)
{
	unsigned short w;
	int bass = emu->bass_level;
	int treble = emu->treble_level;

	if (bass < 0 || bass > 11 || treble < 0 || treble > 11)
		return;
	EMU8000_INIT4_WRITE(emu, 0x01, bass_parm[bass][0]);
	EMU8000_INIT4_WRITE(emu, 0x11, bass_parm[bass][1]);
	EMU8000_INIT3_WRITE(emu, 0x11, treble_parm[treble][0]);
	EMU8000_INIT3_WRITE(emu, 0x13, treble_parm[treble][1]);
	EMU8000_INIT3_WRITE(emu, 0x1b, treble_parm[treble][2]);
	EMU8000_INIT4_WRITE(emu, 0x07, treble_parm[treble][3]);
	EMU8000_INIT4_WRITE(emu, 0x0b, treble_parm[treble][4]);
	EMU8000_INIT4_WRITE(emu, 0x0d, treble_parm[treble][5]);
	EMU8000_INIT4_WRITE(emu, 0x17, treble_parm[treble][6]);
	EMU8000_INIT4_WRITE(emu, 0x19, treble_parm[treble][7]);
	w = bass_parm[bass][2] + treble_parm[treble][8];
	EMU8000_INIT4_WRITE(emu, 0x15, (unsigned short)(w + 0x0262));
	EMU8000_INIT4_WRITE(emu, 0x1d, (unsigned short)(w + 0x8362));
}