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
typedef  enum hdmi_nups { ____Placeholder_hdmi_nups } hdmi_nups ;

/* Variables and functions */
#define  HDMI_NUPS_BOTH 131 
#define  HDMI_NUPS_HORIZONTAL 130 
#define  HDMI_NUPS_UNKNOWN 129 
#define  HDMI_NUPS_VERTICAL 128 

__attribute__((used)) static const char *hdmi_nups_get_name(enum hdmi_nups nups)
{
	switch (nups) {
	case HDMI_NUPS_UNKNOWN:
		return "Unknown Non-uniform Scaling";
	case HDMI_NUPS_HORIZONTAL:
		return "Horizontally Scaled";
	case HDMI_NUPS_VERTICAL:
		return "Vertically Scaled";
	case HDMI_NUPS_BOTH:
		return "Horizontally and Vertically Scaled";
	}
	return "Invalid";
}