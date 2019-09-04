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
struct sonicvibes {int enable; size_t c_dma_size; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,size_t) ; 
 struct sonicvibes* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 size_t snd_sonicvibes_getdmac (struct sonicvibes*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_sonicvibes_capture_pointer(struct snd_pcm_substream *substream)
{
	struct sonicvibes *sonic = snd_pcm_substream_chip(substream);
	size_t ptr;
	if (!(sonic->enable & 2))
		return 0;
	ptr = sonic->c_dma_size - snd_sonicvibes_getdmac(sonic);
	return bytes_to_frames(substream->runtime, ptr);
}