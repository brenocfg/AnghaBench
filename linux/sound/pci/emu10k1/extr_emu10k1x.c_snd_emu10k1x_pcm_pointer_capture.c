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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ buffer_size; struct emu10k1x_pcm* private_data; } ;
struct emu10k1x_pcm {int /*<<< orphan*/  running; } ;
struct emu10k1x {int dummy; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAPTURE_POINTER ; 
 scalar_t__ bytes_to_frames (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1x_ptr_read (struct emu10k1x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct emu10k1x* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t
snd_emu10k1x_pcm_pointer_capture(struct snd_pcm_substream *substream)
{
	struct emu10k1x *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct emu10k1x_pcm *epcm = runtime->private_data;
	snd_pcm_uframes_t ptr;

	if (!epcm->running)
		return 0;

	ptr = bytes_to_frames(runtime, snd_emu10k1x_ptr_read(emu, CAPTURE_POINTER, 0));
	if (ptr >= runtime->buffer_size)
		ptr -= runtime->buffer_size;

	return ptr;
}