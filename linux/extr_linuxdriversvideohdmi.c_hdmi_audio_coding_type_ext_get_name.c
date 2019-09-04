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
typedef  enum hdmi_audio_coding_type_ext { ____Placeholder_hdmi_audio_coding_type_ext } hdmi_audio_coding_type_ext ;

/* Variables and functions */
#define  HDMI_AUDIO_CODING_TYPE_EXT_CT 137 
#define  HDMI_AUDIO_CODING_TYPE_EXT_DRA 136 
#define  HDMI_AUDIO_CODING_TYPE_EXT_HE_AAC 135 
#define  HDMI_AUDIO_CODING_TYPE_EXT_HE_AAC_V2 134 
#define  HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_AAC_LC 133 
#define  HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_AAC_LC_SURROUND 132 
#define  HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC 131 
#define  HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC_SURROUND 130 
#define  HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC_V2 129 
#define  HDMI_AUDIO_CODING_TYPE_EXT_MPEG_SURROUND 128 

__attribute__((used)) static const char *
hdmi_audio_coding_type_ext_get_name(enum hdmi_audio_coding_type_ext ctx)
{
	if (ctx < 0 || ctx > 0x1f)
		return "Invalid";

	switch (ctx) {
	case HDMI_AUDIO_CODING_TYPE_EXT_CT:
		return "Refer to CT";
	case HDMI_AUDIO_CODING_TYPE_EXT_HE_AAC:
		return "HE AAC";
	case HDMI_AUDIO_CODING_TYPE_EXT_HE_AAC_V2:
		return "HE AAC v2";
	case HDMI_AUDIO_CODING_TYPE_EXT_MPEG_SURROUND:
		return "MPEG SURROUND";
	case HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC:
		return "MPEG-4 HE AAC";
	case HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC_V2:
		return "MPEG-4 HE AAC v2";
	case HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_AAC_LC:
		return "MPEG-4 AAC LC";
	case HDMI_AUDIO_CODING_TYPE_EXT_DRA:
		return "DRA";
	case HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC_SURROUND:
		return "MPEG-4 HE AAC + MPEG Surround";
	case HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_AAC_LC_SURROUND:
		return "MPEG-4 AAC LC + MPEG Surround";
	}
	return "Reserved";
}