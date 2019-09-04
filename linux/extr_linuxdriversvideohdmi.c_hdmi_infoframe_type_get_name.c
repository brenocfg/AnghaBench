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
typedef  enum hdmi_infoframe_type { ____Placeholder_hdmi_infoframe_type } hdmi_infoframe_type ;

/* Variables and functions */
#define  HDMI_INFOFRAME_TYPE_AUDIO 131 
#define  HDMI_INFOFRAME_TYPE_AVI 130 
#define  HDMI_INFOFRAME_TYPE_SPD 129 
#define  HDMI_INFOFRAME_TYPE_VENDOR 128 

__attribute__((used)) static const char *hdmi_infoframe_type_get_name(enum hdmi_infoframe_type type)
{
	if (type < 0x80 || type > 0x9f)
		return "Invalid";
	switch (type) {
	case HDMI_INFOFRAME_TYPE_VENDOR:
		return "Vendor";
	case HDMI_INFOFRAME_TYPE_AVI:
		return "Auxiliary Video Information (AVI)";
	case HDMI_INFOFRAME_TYPE_SPD:
		return "Source Product Description (SPD)";
	case HDMI_INFOFRAME_TYPE_AUDIO:
		return "Audio";
	}
	return "Reserved";
}