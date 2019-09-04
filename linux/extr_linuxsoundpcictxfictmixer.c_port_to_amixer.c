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
typedef  enum MIXER_PORT_T { ____Placeholder_MIXER_PORT_T } MIXER_PORT_T ;
typedef  enum CT_AMIXER_CTL { ____Placeholder_CT_AMIXER_CTL } CT_AMIXER_CTL ;

/* Variables and functions */
 int AMIXER_LINEIN ; 
 int AMIXER_MASTER_F_C ; 
 int AMIXER_MIC ; 
 int AMIXER_PCM_C ; 
 int AMIXER_PCM_F ; 
 int AMIXER_PCM_R ; 
 int AMIXER_PCM_S ; 
 int AMIXER_SPDIFI ; 
 int AMIXER_SPDIFO ; 
 int AMIXER_WAVE_C ; 
 int AMIXER_WAVE_F ; 
 int AMIXER_WAVE_R ; 
 int AMIXER_WAVE_S ; 
#define  MIX_LINE_IN 140 
#define  MIX_MIC_IN 139 
#define  MIX_PCMI_CENTLFE 138 
#define  MIX_PCMI_FRONT 137 
#define  MIX_PCMI_REAR 136 
#define  MIX_PCMI_SURROUND 135 
#define  MIX_PCMO_FRONT 134 
#define  MIX_SPDIF_IN 133 
#define  MIX_SPDIF_OUT 132 
#define  MIX_WAVE_CENTLFE 131 
#define  MIX_WAVE_FRONT 130 
#define  MIX_WAVE_REAR 129 
#define  MIX_WAVE_SURROUND 128 

__attribute__((used)) static enum CT_AMIXER_CTL port_to_amixer(enum MIXER_PORT_T type)
{
	switch (type) {
	case MIX_WAVE_FRONT:	return AMIXER_WAVE_F;
	case MIX_WAVE_SURROUND:	return AMIXER_WAVE_S;
	case MIX_WAVE_CENTLFE:	return AMIXER_WAVE_C;
	case MIX_WAVE_REAR:	return AMIXER_WAVE_R;
	case MIX_PCMO_FRONT:	return AMIXER_MASTER_F_C;
	case MIX_SPDIF_OUT:	return AMIXER_SPDIFO;
	case MIX_LINE_IN:	return AMIXER_LINEIN;
	case MIX_MIC_IN:	return AMIXER_MIC;
	case MIX_SPDIF_IN:	return AMIXER_SPDIFI;
	case MIX_PCMI_FRONT:	return AMIXER_PCM_F;
	case MIX_PCMI_SURROUND:	return AMIXER_PCM_S;
	case MIX_PCMI_CENTLFE:	return AMIXER_PCM_C;
	case MIX_PCMI_REAR:	return AMIXER_PCM_R;
	default: 		return 0;
	}
}