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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_dma_ptr (int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int default_read_copy_kernel(struct snd_pcm_substream *substream,
				    int channel, unsigned long hwoff,
				    void *buf, unsigned long bytes)
{
	memcpy(buf, get_dma_ptr(substream->runtime, channel, hwoff), bytes);
	return 0;
}