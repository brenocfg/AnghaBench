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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ buffer_size; struct snd_emu10k1_pcm* private_data; } ;
struct snd_emu10k1_pcm {int /*<<< orphan*/  running; } ;
struct snd_emu10k1 {TYPE_1__* card; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPTURE_POINTER ; 
 scalar_t__ bytes_to_frames (struct snd_pcm_runtime*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ snd_emu10k1_ptr20_read (struct snd_emu10k1*,int /*<<< orphan*/ ,int) ; 
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t
snd_p16v_pcm_pointer_capture(struct snd_pcm_substream *substream)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_emu10k1_pcm *epcm = runtime->private_data;
	snd_pcm_uframes_t ptr, ptr1, ptr2 = 0;
	int channel = 0;

	if (!epcm->running)
		return 0;

	ptr1 = snd_emu10k1_ptr20_read(emu, CAPTURE_POINTER, channel);
	ptr2 = bytes_to_frames(runtime, ptr1);
	ptr=ptr2;
	if (ptr >= runtime->buffer_size) {
		ptr -= runtime->buffer_size;
		dev_warn(emu->card->dev, "buffer capture limited!\n");
	}
	/*
	dev_dbg(emu->card->dev, "ptr1 = 0x%lx, ptr2=0x%lx, ptr=0x%lx, "
	       "buffer_size = 0x%x, period_size = 0x%x, bits=%d, rate=%d\n",
	       ptr1, ptr2, ptr, (int)runtime->buffer_size,
	       (int)runtime->period_size, (int)runtime->frame_bits,
	       (int)runtime->rate);
	*/
	return ptr;
}