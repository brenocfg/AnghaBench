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
typedef  enum hdmi_audio_sample_frequency { ____Placeholder_hdmi_audio_sample_frequency } hdmi_audio_sample_frequency ;

/* Variables and functions */
#define  HDMI_AUDIO_SAMPLE_FREQUENCY_176400 135 
#define  HDMI_AUDIO_SAMPLE_FREQUENCY_192000 134 
#define  HDMI_AUDIO_SAMPLE_FREQUENCY_32000 133 
#define  HDMI_AUDIO_SAMPLE_FREQUENCY_44100 132 
#define  HDMI_AUDIO_SAMPLE_FREQUENCY_48000 131 
#define  HDMI_AUDIO_SAMPLE_FREQUENCY_88200 130 
#define  HDMI_AUDIO_SAMPLE_FREQUENCY_96000 129 
#define  HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM 128 

__attribute__((used)) static const char *
hdmi_audio_sample_frequency_get_name(enum hdmi_audio_sample_frequency freq)
{
	switch (freq) {
	case HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM:
		return "Refer to Stream Header";
	case HDMI_AUDIO_SAMPLE_FREQUENCY_32000:
		return "32 kHz";
	case HDMI_AUDIO_SAMPLE_FREQUENCY_44100:
		return "44.1 kHz (CD)";
	case HDMI_AUDIO_SAMPLE_FREQUENCY_48000:
		return "48 kHz";
	case HDMI_AUDIO_SAMPLE_FREQUENCY_88200:
		return "88.2 kHz";
	case HDMI_AUDIO_SAMPLE_FREQUENCY_96000:
		return "96 kHz";
	case HDMI_AUDIO_SAMPLE_FREQUENCY_176400:
		return "176.4 kHz";
	case HDMI_AUDIO_SAMPLE_FREQUENCY_192000:
		return "192 kHz";
	}
	return "Invalid";
}