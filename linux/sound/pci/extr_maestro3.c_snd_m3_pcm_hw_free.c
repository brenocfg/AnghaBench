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
struct m3_dma {scalar_t__ buffer_addr; } ;
struct TYPE_2__ {struct m3_dma* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_m3_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct m3_dma *s;
	
	if (substream->runtime->private_data == NULL)
		return 0;
	s = substream->runtime->private_data;
	snd_pcm_lib_free_pages(substream);
	s->buffer_addr = 0;
	return 0;
}