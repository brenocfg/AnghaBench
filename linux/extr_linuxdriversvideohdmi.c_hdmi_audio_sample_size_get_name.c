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
typedef  enum hdmi_audio_sample_size { ____Placeholder_hdmi_audio_sample_size } hdmi_audio_sample_size ;

/* Variables and functions */
#define  HDMI_AUDIO_SAMPLE_SIZE_16 131 
#define  HDMI_AUDIO_SAMPLE_SIZE_20 130 
#define  HDMI_AUDIO_SAMPLE_SIZE_24 129 
#define  HDMI_AUDIO_SAMPLE_SIZE_STREAM 128 

__attribute__((used)) static const char *
hdmi_audio_sample_size_get_name(enum hdmi_audio_sample_size sample_size)
{
	switch (sample_size) {
	case HDMI_AUDIO_SAMPLE_SIZE_STREAM:
		return "Refer to Stream Header";
	case HDMI_AUDIO_SAMPLE_SIZE_16:
		return "16 bit";
	case HDMI_AUDIO_SAMPLE_SIZE_20:
		return "20 bit";
	case HDMI_AUDIO_SAMPLE_SIZE_24:
		return "24 bit";
	}
	return "Invalid";
}