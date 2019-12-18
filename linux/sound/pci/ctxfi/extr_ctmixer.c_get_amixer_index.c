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
typedef  enum CT_AMIXER_CTL { ____Placeholder_CT_AMIXER_CTL } CT_AMIXER_CTL ;
typedef  enum CTALSA_MIXER_CTL { ____Placeholder_CTALSA_MIXER_CTL } CTALSA_MIXER_CTL ;

/* Variables and functions */
 int AMIXER_LINEIN ; 
 int AMIXER_LINEIN_C ; 
 int AMIXER_MASTER_F ; 
 int AMIXER_MASTER_F_C ; 
 int AMIXER_MIC ; 
 int AMIXER_MIC_C ; 
 int AMIXER_PCM_F ; 
 int AMIXER_PCM_F_C ; 
 int AMIXER_SPDIFI ; 
 int AMIXER_SPDIFI_C ; 
 int AMIXER_SPDIFO ; 
 int AMIXER_WAVE_C ; 
 int AMIXER_WAVE_F ; 
 int AMIXER_WAVE_R ; 
 int AMIXER_WAVE_S ; 
#define  MIXER_LINEIN_C 146 
#define  MIXER_LINEIN_C_S 145 
#define  MIXER_LINEIN_P 144 
#define  MIXER_MASTER_C 143 
#define  MIXER_MASTER_P 142 
#define  MIXER_MIC_C 141 
#define  MIXER_MIC_C_S 140 
#define  MIXER_MIC_P 139 
#define  MIXER_PCM_C 138 
#define  MIXER_PCM_C_S 137 
#define  MIXER_PCM_P 136 
#define  MIXER_SPDIFI_C 135 
#define  MIXER_SPDIFI_C_S 134 
#define  MIXER_SPDIFI_P 133 
#define  MIXER_SPDIFO_P 132 
#define  MIXER_WAVEC_P 131 
#define  MIXER_WAVEF_P 130 
#define  MIXER_WAVER_P 129 
#define  MIXER_WAVES_P 128 
 int NUM_CT_AMIXERS ; 

__attribute__((used)) static enum CT_AMIXER_CTL get_amixer_index(enum CTALSA_MIXER_CTL alsa_index)
{
	switch (alsa_index) {
	case MIXER_MASTER_P:	return AMIXER_MASTER_F;
	case MIXER_MASTER_C:	return AMIXER_MASTER_F_C;
	case MIXER_PCM_P:	return AMIXER_PCM_F;
	case MIXER_PCM_C:
	case MIXER_PCM_C_S:	return AMIXER_PCM_F_C;
	case MIXER_LINEIN_P:	return AMIXER_LINEIN;
	case MIXER_LINEIN_C:
	case MIXER_LINEIN_C_S:	return AMIXER_LINEIN_C;
	case MIXER_MIC_P:	return AMIXER_MIC;
	case MIXER_MIC_C:
	case MIXER_MIC_C_S:	return AMIXER_MIC_C;
	case MIXER_SPDIFI_P:	return AMIXER_SPDIFI;
	case MIXER_SPDIFI_C:
	case MIXER_SPDIFI_C_S:	return AMIXER_SPDIFI_C;
	case MIXER_SPDIFO_P:	return AMIXER_SPDIFO;
	case MIXER_WAVEF_P:	return AMIXER_WAVE_F;
	case MIXER_WAVES_P:	return AMIXER_WAVE_S;
	case MIXER_WAVEC_P:	return AMIXER_WAVE_C;
	case MIXER_WAVER_P:	return AMIXER_WAVE_R;
	default:		return NUM_CT_AMIXERS;
	}
}