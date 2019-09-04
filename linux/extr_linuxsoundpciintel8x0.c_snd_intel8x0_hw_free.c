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
struct intel8x0 {scalar_t__ fix_nocache; } ;
struct ichdev {scalar_t__ page_attr_changed; scalar_t__ pcm_open_flag; int /*<<< orphan*/  pcm; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_bytes; int /*<<< orphan*/  dma_area; } ;

/* Variables and functions */
 int /*<<< orphan*/  fill_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ichdev* get_ichdev (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_ac97_pcm_close (int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct intel8x0* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_intel8x0_hw_free(struct snd_pcm_substream *substream)
{
	struct intel8x0 *chip = snd_pcm_substream_chip(substream);
	struct ichdev *ichdev = get_ichdev(substream);

	if (ichdev->pcm_open_flag) {
		snd_ac97_pcm_close(ichdev->pcm);
		ichdev->pcm_open_flag = 0;
	}
	if (chip->fix_nocache && ichdev->page_attr_changed) {
		fill_nocache(substream->runtime->dma_area, substream->runtime->dma_bytes, 0);
		ichdev->page_attr_changed = 0;
	}
	return snd_pcm_lib_free_pages(substream);
}