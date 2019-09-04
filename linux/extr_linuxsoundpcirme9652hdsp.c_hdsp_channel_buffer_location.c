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
struct hdsp {int max_channels; int* channel_map; char* capture_buffer; char* playback_buffer; } ;

/* Variables and functions */
 int HDSP_CHANNEL_BUFFER_BYTES ; 
 int SNDRV_PCM_STREAM_CAPTURE ; 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static char *hdsp_channel_buffer_location(struct hdsp *hdsp,
					     int stream,
					     int channel)

{
	int mapped_channel;

        if (snd_BUG_ON(channel < 0 || channel >= hdsp->max_channels))
		return NULL;

	if ((mapped_channel = hdsp->channel_map[channel]) < 0)
		return NULL;

	if (stream == SNDRV_PCM_STREAM_CAPTURE)
		return hdsp->capture_buffer + (mapped_channel * HDSP_CHANNEL_BUFFER_BYTES);
	else
		return hdsp->playback_buffer + (mapped_channel * HDSP_CHANNEL_BUFFER_BYTES);
}