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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_intelhad {int /*<<< orphan*/  connected; } ;
typedef  int snd_pcm_uframes_t ;
struct TYPE_2__ {int buffer_size; } ;

/* Variables and functions */
 int SNDRV_PCM_POS_XRUN ; 
 int bytes_to_frames (TYPE_1__*,int) ; 
 int had_process_ringbuf (struct snd_pcm_substream*,struct snd_intelhad*) ; 
 struct snd_intelhad* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t had_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct snd_intelhad *intelhaddata;
	int len;

	intelhaddata = snd_pcm_substream_chip(substream);

	if (!intelhaddata->connected)
		return SNDRV_PCM_POS_XRUN;

	len = had_process_ringbuf(substream, intelhaddata);
	if (len < 0)
		return SNDRV_PCM_POS_XRUN;
	len = bytes_to_frames(substream->runtime, len);
	/* wrapping may happen when periods=1 */
	len %= substream->runtime->buffer_size;
	return len;
}