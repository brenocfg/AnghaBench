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
struct snd_pcm_runtime {scalar_t__ dma_addr; } ;
struct axg_fifo {int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIFO_STATUS2 ; 
 struct axg_fifo* axg_fifo_data (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  bytes_to_frames (struct snd_pcm_runtime*,unsigned int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static snd_pcm_uframes_t axg_fifo_pcm_pointer(struct snd_pcm_substream *ss)
{
	struct axg_fifo *fifo = axg_fifo_data(ss);
	struct snd_pcm_runtime *runtime = ss->runtime;
	unsigned int addr;

	regmap_read(fifo->map, FIFO_STATUS2, &addr);

	return bytes_to_frames(runtime, addr - (unsigned int)runtime->dma_addr);
}