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
struct hdac_device {int dummy; } ;

/* Variables and functions */
 int hdmi_channel_allocation_spk_alloc_blk (struct hdac_device*,int,int) ; 
 int hdmi_manual_channel_allocation (int,unsigned char*) ; 

int snd_hdac_channel_allocation(struct hdac_device *hdac, int spk_alloc,
		int channels, bool chmap_set, bool non_pcm, unsigned char *map)
{
	int ca;

	if (!non_pcm && chmap_set)
		ca = hdmi_manual_channel_allocation(channels, map);
	else
		ca = hdmi_channel_allocation_spk_alloc_blk(hdac,
					spk_alloc, channels);

	if (ca < 0)
		ca = 0;

	return ca;
}