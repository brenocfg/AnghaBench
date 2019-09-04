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
struct snd_opl3_drum_voice {int dummy; } ;
struct snd_opl3 {int drum_reg; int /*<<< orphan*/  (* command ) (struct snd_opl3*,int,unsigned char) ;} ;
struct snd_midi_channel {int dummy; } ;

/* Variables and functions */
#define  OPL3_BASSDRUM_ON 132 
#define  OPL3_CYMBAL_ON 131 
#define  OPL3_HIHAT_ON 130 
 int OPL3_LEFT ; 
 int OPL3_PERCUSSION_ENABLE ; 
 int OPL3_REG_PERCUSSION ; 
#define  OPL3_SNAREDRUM_ON 129 
#define  OPL3_TOMTOM_ON 128 
 struct snd_opl3_drum_voice bass_op1 ; 
 struct snd_opl3_drum_voice cymbal ; 
 struct snd_opl3_drum_voice hihat ; 
 struct snd_opl3_drum_voice snare ; 
 unsigned char* snd_opl3_drum_table ; 
 int /*<<< orphan*/  snd_opl3_drum_vol_set (struct snd_opl3*,struct snd_opl3_drum_voice*,int,struct snd_midi_channel*) ; 
 int /*<<< orphan*/  stub1 (struct snd_opl3*,int,unsigned char) ; 
 struct snd_opl3_drum_voice tomtom ; 

void snd_opl3_drum_switch(struct snd_opl3 *opl3, int note, int vel, int on_off,
			  struct snd_midi_channel *chan)
{
	unsigned char drum_mask;
	struct snd_opl3_drum_voice *drum_voice;

	if (!(opl3->drum_reg & OPL3_PERCUSSION_ENABLE))
		return;

	if ((note < 35) || (note > 81))
		return;
	drum_mask = snd_opl3_drum_table[note - 35];

	if (on_off) {
		switch (drum_mask) {
		case OPL3_BASSDRUM_ON:
			drum_voice = &bass_op1;
			break;
		case OPL3_HIHAT_ON:
			drum_voice = &hihat;
			break;
		case OPL3_SNAREDRUM_ON:
			drum_voice = &snare;
			break;
		case OPL3_TOMTOM_ON:
			drum_voice = &tomtom;
			break;
		case OPL3_CYMBAL_ON:
			drum_voice = &cymbal;
			break;
		default:
			drum_voice = &tomtom;
		}

		snd_opl3_drum_vol_set(opl3, drum_voice, vel, chan);
		opl3->drum_reg |= drum_mask;
	} else {
		opl3->drum_reg &= ~drum_mask;
	}
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_PERCUSSION,
			 opl3->drum_reg);
}