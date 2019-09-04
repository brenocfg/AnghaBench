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
struct page {int dummy; } ;
struct TYPE_2__ {scalar_t__ dma_area; } ;

/* Variables and functions */
 struct page* vmalloc_to_page (scalar_t__) ; 

struct page *snd_pcm_lib_get_vmalloc_page(struct snd_pcm_substream *substream,
					  unsigned long offset)
{
	return vmalloc_to_page(substream->runtime->dma_area + offset);
}