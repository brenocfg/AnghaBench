#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; struct device* dev; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct snd_pcm_substream {TYPE_2__ dma_buffer; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages1 (struct snd_pcm_substream*,size_t,size_t) ; 

void snd_pcm_lib_preallocate_pages(struct snd_pcm_substream *substream,
				  int type, struct device *data,
				  size_t size, size_t max)
{
	substream->dma_buffer.dev.type = type;
	substream->dma_buffer.dev.dev = data;
	snd_pcm_lib_preallocate_pages1(substream, size, max);
}