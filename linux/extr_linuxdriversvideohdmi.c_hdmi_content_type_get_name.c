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
typedef  enum hdmi_content_type { ____Placeholder_hdmi_content_type } hdmi_content_type ;

/* Variables and functions */
#define  HDMI_CONTENT_TYPE_CINEMA 131 
#define  HDMI_CONTENT_TYPE_GAME 130 
#define  HDMI_CONTENT_TYPE_GRAPHICS 129 
#define  HDMI_CONTENT_TYPE_PHOTO 128 

__attribute__((used)) static const char *
hdmi_content_type_get_name(enum hdmi_content_type content_type)
{
	switch (content_type) {
	case HDMI_CONTENT_TYPE_GRAPHICS:
		return "Graphics";
	case HDMI_CONTENT_TYPE_PHOTO:
		return "Photo";
	case HDMI_CONTENT_TYPE_CINEMA:
		return "Cinema";
	case HDMI_CONTENT_TYPE_GAME:
		return "Game";
	}
	return "Invalid";
}