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
struct TYPE_5__ {int fm2frq2; } ;
struct TYPE_6__ {TYPE_2__ parm; } ;
struct snd_emux_voice {int /*<<< orphan*/  ch; TYPE_1__* chan; TYPE_3__ reg; } ;
struct snd_emu10k1 {int dummy; } ;
struct TYPE_4__ {int gm_modulation; int midi_pressure; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM2FRQ2 ; 
 int /*<<< orphan*/  LIMITVALUE (short,int,int) ; 
 int MOD_SENSE ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void
set_fm2frq2(struct snd_emu10k1 *hw, struct snd_emux_voice *vp)
{
	unsigned short fm2frq2;
	short pitch;
	unsigned char freq;
	int modulation;

	pitch = (char)(vp->reg.parm.fm2frq2>>8);
	freq = vp->reg.parm.fm2frq2 & 0xff;
	modulation = vp->chan->gm_modulation + vp->chan->midi_pressure;
	pitch += (MOD_SENSE * modulation) / 1200;
	LIMITVALUE(pitch, -128, 127);
	fm2frq2 = ((unsigned char)pitch<<8) | freq;
	snd_emu10k1_ptr_write(hw, FM2FRQ2, vp->ch, fm2frq2);
}