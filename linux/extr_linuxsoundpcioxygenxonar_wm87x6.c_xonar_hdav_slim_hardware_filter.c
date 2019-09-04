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
struct snd_pcm_hardware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wm8776_adc_hardware_filter (unsigned int,struct snd_pcm_hardware*) ; 
 int /*<<< orphan*/  xonar_hdmi_pcm_hardware_filter (unsigned int,struct snd_pcm_hardware*) ; 

__attribute__((used)) static void xonar_hdav_slim_hardware_filter(unsigned int channel,
					    struct snd_pcm_hardware *hardware)
{
	wm8776_adc_hardware_filter(channel, hardware);
	xonar_hdmi_pcm_hardware_filter(channel, hardware);
}