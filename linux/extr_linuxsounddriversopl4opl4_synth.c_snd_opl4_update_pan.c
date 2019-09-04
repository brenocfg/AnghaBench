#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_opl4 {int dummy; } ;
struct opl4_voice {int reg_misc; scalar_t__ number; TYPE_2__* chan; TYPE_1__* sound; } ;
struct TYPE_4__ {int* control; int /*<<< orphan*/  drum_channel; } ;
struct TYPE_3__ {int panpot; } ;

/* Variables and functions */
 size_t MIDI_CTL_MSB_PAN ; 
 int OPL4_PAN_POT_MASK ; 
 scalar_t__ OPL4_REG_MISC ; 
 int /*<<< orphan*/  snd_opl4_write (struct snd_opl4*,scalar_t__,int) ; 

__attribute__((used)) static void snd_opl4_update_pan(struct snd_opl4 *opl4, struct opl4_voice *voice)
{
	int pan = voice->sound->panpot;

	if (!voice->chan->drum_channel)
		pan += (voice->chan->control[MIDI_CTL_MSB_PAN] - 0x40) >> 3;
	if (pan < -7)
		pan = -7;
	else if (pan > 7)
		pan = 7;
	voice->reg_misc = (voice->reg_misc & ~OPL4_PAN_POT_MASK)
		| (pan & OPL4_PAN_POT_MASK);
	snd_opl4_write(opl4, OPL4_REG_MISC + voice->number, voice->reg_misc);
}