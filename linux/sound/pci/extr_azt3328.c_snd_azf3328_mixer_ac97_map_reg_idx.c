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

/* Variables and functions */
 unsigned short AC97_3D_CONTROL ; 
#define  AC97_EXTENDED_ID 152 
#define  AC97_EXTENDED_STATUS 151 
#define  AC97_POWERDOWN 150 
#define  AC97_VENDOR_ID1 149 
#define  AC97_VENDOR_ID2 148 
#define  AZF_AC97_REG_EMU_IO_READ 147 
#define  AZF_AC97_REG_EMU_IO_RW 146 
 unsigned short AZF_AC97_REG_REAL_IO_RW ; 
#define  AZF_AC97_REG_REAL_IO_WRITE 145 
 unsigned short AZF_AC97_REG_UNSUPPORTED ; 
 unsigned short AZF_REG_MASK ; 
#define  IDX_MIXER_ADVCTL1 144 
#define  IDX_MIXER_ADVCTL2 143 
#define  IDX_MIXER_AUX 142 
#define  IDX_MIXER_BASSTREBLE 141 
#define  IDX_MIXER_CDAUDIO 140 
#define  IDX_MIXER_FMSYNTH 139 
#define  IDX_MIXER_LINEIN 138 
#define  IDX_MIXER_MIC 137 
#define  IDX_MIXER_MODEMIN 136 
#define  IDX_MIXER_MODEMOUT 135 
#define  IDX_MIXER_PCBEEP 134 
#define  IDX_MIXER_PLAY_MASTER 133 
#define  IDX_MIXER_REC_SELECT 132 
#define  IDX_MIXER_REC_VOLUME 131 
#define  IDX_MIXER_RESET 130 
#define  IDX_MIXER_VIDEO 129 
#define  IDX_MIXER_WAVEOUT 128 

__attribute__((used)) static unsigned short
snd_azf3328_mixer_ac97_map_reg_idx(unsigned short reg)
{
	static const struct {
		unsigned short azf_reg;
	} azf_reg_mapper[] = {
		/* Especially when taking into consideration
		 * mono/stereo-based sequence of azf vs. AC97 control series,
		 * it's quite obvious that azf simply got rid
		 * of the AC97_HEADPHONE control at its intended offset,
		 * thus shifted _all_ controls by one,
		 * and _then_ simply added it as an FMSYNTH control at the end,
		 * to make up for the offset.
		 * This means we'll have to translate indices here as
		 * needed and then do some tiny AC97 patch action
		 * (snd_ac97_rename_vol_ctl() etc.) - that's it.
		 */
		{ /* AC97_RESET */ IDX_MIXER_RESET
			| AZF_AC97_REG_REAL_IO_WRITE
			| AZF_AC97_REG_EMU_IO_READ },
		{ /* AC97_MASTER */ IDX_MIXER_PLAY_MASTER },
		 /* note large shift: AC97_HEADPHONE to IDX_MIXER_FMSYNTH! */
		{ /* AC97_HEADPHONE */ IDX_MIXER_FMSYNTH },
		{ /* AC97_MASTER_MONO */ IDX_MIXER_MODEMOUT },
		{ /* AC97_MASTER_TONE */ IDX_MIXER_BASSTREBLE },
		{ /* AC97_PC_BEEP */ IDX_MIXER_PCBEEP },
		{ /* AC97_PHONE */ IDX_MIXER_MODEMIN },
		{ /* AC97_MIC */ IDX_MIXER_MIC },
		{ /* AC97_LINE */ IDX_MIXER_LINEIN },
		{ /* AC97_CD */ IDX_MIXER_CDAUDIO },
		{ /* AC97_VIDEO */ IDX_MIXER_VIDEO },
		{ /* AC97_AUX */ IDX_MIXER_AUX },
		{ /* AC97_PCM */ IDX_MIXER_WAVEOUT },
		{ /* AC97_REC_SEL */ IDX_MIXER_REC_SELECT },
		{ /* AC97_REC_GAIN */ IDX_MIXER_REC_VOLUME },
		{ /* AC97_REC_GAIN_MIC */ AZF_AC97_REG_EMU_IO_RW },
		{ /* AC97_GENERAL_PURPOSE */ IDX_MIXER_ADVCTL2 },
		{ /* AC97_3D_CONTROL */ IDX_MIXER_ADVCTL1 },
	};

	unsigned short reg_azf = AZF_AC97_REG_UNSUPPORTED;

	/* azf3328 supports the low-numbered and low-spec:ed range
	   of AC97 regs only */
	if (reg <= AC97_3D_CONTROL) {
		unsigned short reg_idx = reg / 2;
		reg_azf = azf_reg_mapper[reg_idx].azf_reg;
		/* a translation-only entry means it's real read/write: */
		if (!(reg_azf & ~AZF_REG_MASK))
			reg_azf |= AZF_AC97_REG_REAL_IO_RW;
	} else {
		switch (reg) {
		case AC97_POWERDOWN:
			reg_azf = AZF_AC97_REG_EMU_IO_RW;
			break;
		case AC97_EXTENDED_ID:
			reg_azf = AZF_AC97_REG_EMU_IO_READ;
			break;
		case AC97_EXTENDED_STATUS:
			/* I don't know what the h*ll AC97 layer
			 * would consult this _extended_ register for
			 * given a base-AC97-advertised card,
			 * but let's just emulate it anyway :-P
			 */
			reg_azf = AZF_AC97_REG_EMU_IO_RW;
			break;
		case AC97_VENDOR_ID1:
		case AC97_VENDOR_ID2:
			reg_azf = AZF_AC97_REG_EMU_IO_READ;
			break;
		}
	}
	return reg_azf;
}