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
struct snd_opl3_voice {scalar_t__ state; scalar_t__ time; int /*<<< orphan*/  keyon_reg; } ;
struct snd_opl3 {int /*<<< orphan*/  use_time; struct snd_opl3_voice* voices; int /*<<< orphan*/  (* command ) (struct snd_opl3*,unsigned short,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int MAX_OPL2_VOICES ; 
 int MAX_OPL3_VOICES ; 
 unsigned short OPL3_LEFT ; 
 unsigned char OPL3_REG_KEYON_BLOCK ; 
 unsigned short OPL3_RIGHT ; 
 void* SNDRV_OPL3_ST_OFF ; 
 scalar_t__ SNDRV_OPL3_ST_ON_4OP ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct snd_opl3*,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_opl3_kill_voice(struct snd_opl3 *opl3, int voice)
{
	unsigned short reg_side;
	unsigned char voice_offset;
	unsigned short opl3_reg;

	struct snd_opl3_voice *vp, *vp2;

	if (snd_BUG_ON(voice >= MAX_OPL3_VOICES))
		return;

	vp = &opl3->voices[voice];
	if (voice < MAX_OPL2_VOICES) {
		/* Left register block for voices 0 .. 8 */
		reg_side = OPL3_LEFT;
		voice_offset = voice;
	} else {
		/* Right register block for voices 9 .. 17 */
		reg_side = OPL3_RIGHT;
		voice_offset = voice - MAX_OPL2_VOICES;
	}

	/* kill voice */
#ifdef DEBUG_MIDI
	snd_printk(KERN_DEBUG "  --> kill voice %i\n", voice);
#endif
	opl3_reg = reg_side | (OPL3_REG_KEYON_BLOCK + voice_offset);
	/* clear Key ON bit */
	opl3->command(opl3, opl3_reg, vp->keyon_reg);

	/* do the bookkeeping */
	vp->time = opl3->use_time++;

	if (vp->state == SNDRV_OPL3_ST_ON_4OP) {
		vp2 = &opl3->voices[voice + 3];

		vp2->time = opl3->use_time++;
		vp2->state = SNDRV_OPL3_ST_OFF;
	}
	vp->state = SNDRV_OPL3_ST_OFF;
#ifdef DEBUG_ALLOC
	debug_alloc(opl3, "note off", voice);
#endif

}