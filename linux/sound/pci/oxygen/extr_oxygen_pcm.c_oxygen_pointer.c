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
typedef  scalar_t__ u32 ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ dma_addr; } ;
struct oxygen {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  bytes_to_frames (struct snd_pcm_runtime*,scalar_t__) ; 
 int /*<<< orphan*/ * channel_base_registers ; 
 scalar_t__ oxygen_read32 (struct oxygen*,int /*<<< orphan*/ ) ; 
 unsigned int oxygen_substream_channel (struct snd_pcm_substream*) ; 
 struct oxygen* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t oxygen_pointer(struct snd_pcm_substream *substream)
{
	struct oxygen *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned int channel = oxygen_substream_channel(substream);
	u32 curr_addr;

	/* no spinlock, this read should be atomic */
	curr_addr = oxygen_read32(chip, channel_base_registers[channel]);
	return bytes_to_frames(runtime, curr_addr - (u32)runtime->dma_addr);
}