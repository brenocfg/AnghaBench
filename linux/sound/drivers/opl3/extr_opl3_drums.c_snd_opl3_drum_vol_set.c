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
struct snd_opl3_drum_voice {size_t voice; size_t op; unsigned char ksl_level; unsigned char feedback_connection; } ;
struct snd_opl3 {int /*<<< orphan*/  (* command ) (struct snd_opl3*,unsigned short,unsigned char) ;} ;
struct snd_midi_channel {int gm_pan; } ;

/* Variables and functions */
 unsigned char OPL3_LEFT ; 
 unsigned char OPL3_REG_FEEDBACK_CONNECTION ; 
 unsigned char OPL3_REG_KSL_LEVEL ; 
 unsigned char OPL3_STEREO_BITS ; 
 unsigned char OPL3_VOICE_TO_LEFT ; 
 unsigned char OPL3_VOICE_TO_RIGHT ; 
 int /*<<< orphan*/  snd_opl3_calc_volume (unsigned char*,int,struct snd_midi_channel*) ; 
 unsigned char** snd_opl3_regmap ; 
 int /*<<< orphan*/  stub1 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub2 (struct snd_opl3*,unsigned short,unsigned char) ; 

__attribute__((used)) static void snd_opl3_drum_vol_set(struct snd_opl3 *opl3,
				  struct snd_opl3_drum_voice *data,
				  int vel, struct snd_midi_channel *chan)
{
	unsigned char op_offset = snd_opl3_regmap[data->voice][data->op];
	unsigned char voice_offset = data->voice;
	unsigned char reg_val;
	unsigned short opl3_reg;

	/* Set OPL3 KSL_LEVEL register */ 
	reg_val = data->ksl_level;
	snd_opl3_calc_volume(&reg_val, vel, chan);
	opl3_reg = OPL3_LEFT | (OPL3_REG_KSL_LEVEL + op_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	/* Set OPL3 FEEDBACK_CONNECTION register */ 
	/* Set output voice connection */
	reg_val = data->feedback_connection | OPL3_STEREO_BITS;
	if (chan->gm_pan < 43)
		reg_val &= ~OPL3_VOICE_TO_RIGHT;
	if (chan->gm_pan > 85)
		reg_val &= ~OPL3_VOICE_TO_LEFT;
	opl3_reg = OPL3_LEFT | (OPL3_REG_FEEDBACK_CONNECTION + voice_offset);
	opl3->command(opl3, opl3_reg, reg_val);
}