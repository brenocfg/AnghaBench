#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fmmod; } ;
struct TYPE_6__ {TYPE_2__ parm; } ;
struct snd_emux_voice {int /*<<< orphan*/  ch; TYPE_1__* chan; TYPE_3__ reg; } ;
struct snd_emu8000 {int dummy; } ;
struct TYPE_4__ {int gm_modulation; int midi_pressure; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU8000_FMMOD_WRITE (struct snd_emu8000*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  LIMITVALUE (short,int,int) ; 
 int MOD_SENSE ; 

__attribute__((used)) static void
set_fmmod(struct snd_emu8000 *hw, struct snd_emux_voice *vp)
{
	unsigned short fmmod;
	short pitch;
	unsigned char cutoff;
	int modulation;

	pitch = (char)(vp->reg.parm.fmmod>>8);
	cutoff = (vp->reg.parm.fmmod & 0xff);
	modulation = vp->chan->gm_modulation + vp->chan->midi_pressure;
	pitch += (MOD_SENSE * modulation) / 1200;
	LIMITVALUE(pitch, -128, 127);
	fmmod = ((unsigned char)pitch<<8) | cutoff;
	EMU8000_FMMOD_WRITE(hw, vp->ch, fmmod);
}