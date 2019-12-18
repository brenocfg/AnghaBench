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
typedef  int /*<<< orphan*/  snd_pcm_format_t ;

/* Variables and functions */
 unsigned int HDMI_BIT_WIDTH_16_BIT ; 
 unsigned int HDMI_BIT_WIDTH_32_BIT ; 
 int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int get_hdmi_wlen(snd_pcm_format_t format)
{
	return snd_pcm_format_physical_width(format) <= 16 ?
	       HDMI_BIT_WIDTH_16_BIT : HDMI_BIT_WIDTH_32_BIT;
}