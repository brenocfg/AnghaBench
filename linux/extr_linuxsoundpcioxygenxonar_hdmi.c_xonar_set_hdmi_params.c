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
struct xonar_hdmi {int* params; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct oxygen {int dummy; } ;

/* Variables and functions */
 int IEC958_AES3_CON_FS_192000 ; 
 int IEC958_AES3_CON_FS_44100 ; 
 int IEC958_AES3_CON_FS_48000 ; 
 int IEC958_AES3_CON_FS_96000 ; 
 scalar_t__ SNDRV_PCM_FORMAT_S16_LE ; 
 int /*<<< orphan*/  hdmi_write_command (struct oxygen*,int,int,int*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 scalar_t__ params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 

void xonar_set_hdmi_params(struct oxygen *chip, struct xonar_hdmi *hdmi,
			   struct snd_pcm_hw_params *params)
{
	hdmi->params[0] = 0; /* 1 = non-audio */
	switch (params_rate(params)) {
	case 44100:
		hdmi->params[1] = IEC958_AES3_CON_FS_44100;
		break;
	case 48000:
		hdmi->params[1] = IEC958_AES3_CON_FS_48000;
		break;
	default: /* 96000 */
		hdmi->params[1] = IEC958_AES3_CON_FS_96000;
		break;
	case 192000:
		hdmi->params[1] = IEC958_AES3_CON_FS_192000;
		break;
	}
	hdmi->params[2] = params_channels(params) / 2 - 1;
	if (params_format(params) == SNDRV_PCM_FORMAT_S16_LE)
		hdmi->params[3] = 0;
	else
		hdmi->params[3] = 0xc0;
	hdmi->params[4] = 1; /* ? */
	hdmi_write_command(chip, 0x54, 5, hdmi->params);
}