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
struct TYPE_5__ {unsigned int reverb; int /*<<< orphan*/  voldcysus; } ;
struct TYPE_6__ {TYPE_2__ parm; } ;
struct snd_emux_voice {int ch; int ptarget; unsigned int aaux; TYPE_3__ reg; TYPE_1__* chan; struct snd_emu8000* hw; } ;
struct snd_emu8000 {int dummy; } ;
struct TYPE_4__ {scalar_t__* control; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU8000_CPF_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_DCYSUSV_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_PTRX_WRITE (struct snd_emu8000*,int,unsigned int) ; 
 int /*<<< orphan*/  LIMITMAX (unsigned int,int) ; 
 size_t MIDI_CTL_E1_REVERB_DEPTH ; 

__attribute__((used)) static void
trigger_voice(struct snd_emux_voice *vp)
{
	int ch = vp->ch;
	unsigned int temp;
	struct snd_emu8000 *hw;

	hw = vp->hw;

	/* set reverb and pitch target */
	temp = vp->reg.parm.reverb;
	temp += (int)vp->chan->control[MIDI_CTL_E1_REVERB_DEPTH] * 9 / 10;
	LIMITMAX(temp, 255);
	temp = (temp << 8) | (vp->ptarget << 16) | vp->aaux;
	EMU8000_PTRX_WRITE(hw, ch, temp);
	EMU8000_CPF_WRITE(hw, ch, vp->ptarget << 16);
	EMU8000_DCYSUSV_WRITE(hw, ch, vp->reg.parm.voldcysus);
}