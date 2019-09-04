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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_area; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sst_media_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	int ret;

	ret =
		snd_pcm_lib_malloc_pages(substream,
				params_buffer_bytes(params));
	if (ret)
		return ret;
	memset(substream->runtime->dma_area, 0, params_buffer_bytes(params));
	return 0;
}