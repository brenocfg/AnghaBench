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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_CODEC_RESET ; 
 int alc5505_coef_get (struct hda_codec*,int) ; 
 int /*<<< orphan*/  alc5505_coef_set (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  alc5505_dsp_back_from_halt (struct hda_codec*) ; 
 int /*<<< orphan*/  alc5505_dsp_halt (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc5505_dsp_init(struct hda_codec *codec)
{
	unsigned int val;

	alc5505_dsp_halt(codec);
	alc5505_dsp_back_from_halt(codec);
	alc5505_coef_set(codec, 0x61b0, 0x5b14); /* PLL1 control */
	alc5505_coef_set(codec, 0x61b0, 0x5b16);
	alc5505_coef_set(codec, 0x61b4, 0x04132b00); /* PLL2 control */
	alc5505_coef_set(codec, 0x61b4, 0x04132b02);
	alc5505_coef_set(codec, 0x61b8, 0x041f3300); /* PLL3 control*/
	alc5505_coef_set(codec, 0x61b8, 0x041f3302);
	snd_hda_codec_write(codec, 0x51, 0, AC_VERB_SET_CODEC_RESET, 0); /* Function reset */
	alc5505_coef_set(codec, 0x61b8, 0x041b3302);
	alc5505_coef_set(codec, 0x61b8, 0x04173302);
	alc5505_coef_set(codec, 0x61b8, 0x04163302);
	alc5505_coef_set(codec, 0x8800, 0x348b328b); /* DRAM control */
	alc5505_coef_set(codec, 0x8808, 0x00020022); /* DRAM control */
	alc5505_coef_set(codec, 0x8818, 0x00000400); /* DRAM control */

	val = alc5505_coef_get(codec, 0x6200) >> 16; /* Read revision ID */
	if (val <= 3)
		alc5505_coef_set(codec, 0x6220, 0x2002010f); /* I/O PAD Configuration */
	else
		alc5505_coef_set(codec, 0x6220, 0x6002018f);

	alc5505_coef_set(codec, 0x61ac, 0x055525f0); /**/
	alc5505_coef_set(codec, 0x61c0, 0x12230080); /* Clock control */
	alc5505_coef_set(codec, 0x61b4, 0x040e2b02); /* PLL2 control */
	alc5505_coef_set(codec, 0x61bc, 0x010234f8); /* OSC Control */
	alc5505_coef_set(codec, 0x880c, 0x00000004); /* DRAM Function control */
	alc5505_coef_set(codec, 0x880c, 0x00000003);
	alc5505_coef_set(codec, 0x880c, 0x00000010);

#ifdef HALT_REALTEK_ALC5505
	alc5505_dsp_halt(codec);
#endif
}