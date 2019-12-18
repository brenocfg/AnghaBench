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
struct snd_opl3_drum_voice {size_t voice; size_t op; int /*<<< orphan*/  wave_select; int /*<<< orphan*/  feedback_connection; int /*<<< orphan*/  sustain_release; int /*<<< orphan*/  attack_decay; int /*<<< orphan*/  ksl_level; int /*<<< orphan*/  am_vib; } ;
struct snd_opl3 {int /*<<< orphan*/  (* command ) (struct snd_opl3*,unsigned short,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 unsigned char OPL3_LEFT ; 
 unsigned char OPL3_REG_AM_VIB ; 
 unsigned char OPL3_REG_ATTACK_DECAY ; 
 unsigned char OPL3_REG_FEEDBACK_CONNECTION ; 
 unsigned char OPL3_REG_KSL_LEVEL ; 
 unsigned char OPL3_REG_SUSTAIN_RELEASE ; 
 unsigned char OPL3_REG_WAVE_SELECT ; 
 unsigned char** snd_opl3_regmap ; 
 int /*<<< orphan*/  stub1 (struct snd_opl3*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct snd_opl3*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct snd_opl3*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct snd_opl3*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct snd_opl3*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct snd_opl3*,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_opl3_drum_voice_set(struct snd_opl3 *opl3,
				    struct snd_opl3_drum_voice *data)
{
	unsigned char op_offset = snd_opl3_regmap[data->voice][data->op];
	unsigned char voice_offset = data->voice;
	unsigned short opl3_reg;
	
	/* Set OPL3 AM_VIB register */ 
	opl3_reg = OPL3_LEFT | (OPL3_REG_AM_VIB + op_offset);
	opl3->command(opl3, opl3_reg, data->am_vib);

	/* Set OPL3 KSL_LEVEL register */ 
	opl3_reg = OPL3_LEFT | (OPL3_REG_KSL_LEVEL + op_offset);
	opl3->command(opl3, opl3_reg, data->ksl_level);

	/* Set OPL3 ATTACK_DECAY register */ 
	opl3_reg = OPL3_LEFT | (OPL3_REG_ATTACK_DECAY + op_offset);
	opl3->command(opl3, opl3_reg, data->attack_decay);

	/* Set OPL3 SUSTAIN_RELEASE register */ 
	opl3_reg = OPL3_LEFT | (OPL3_REG_SUSTAIN_RELEASE + op_offset);
	opl3->command(opl3, opl3_reg, data->sustain_release);

	/* Set OPL3 FEEDBACK_CONNECTION register */ 
	opl3_reg = OPL3_LEFT | (OPL3_REG_FEEDBACK_CONNECTION + voice_offset);
	opl3->command(opl3, opl3_reg, data->feedback_connection);

	/* Select waveform */
	opl3_reg = OPL3_LEFT | (OPL3_REG_WAVE_SELECT + op_offset);
	opl3->command(opl3, opl3_reg, data->wave_select);
}