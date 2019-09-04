#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* pstr; } ;
struct hdsp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 int EIO ; 
 char* hdsp_channel_buffer_location (struct hdsp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,void*,unsigned long) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 struct hdsp* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_hdsp_playback_copy_kernel(struct snd_pcm_substream *substream,
					 int channel, unsigned long pos,
					 void *src, unsigned long count)
{
	struct hdsp *hdsp = snd_pcm_substream_chip(substream);
	char *channel_buf;

	channel_buf = hdsp_channel_buffer_location(hdsp, substream->pstr->stream, channel);
	if (snd_BUG_ON(!channel_buf))
		return -EIO;
	memcpy(channel_buf + pos, src, count);
	return 0;
}