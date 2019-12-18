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
struct snd_sof_pcm {TYPE_2__* stream; } ;
struct snd_sof_dev {int dummy; } ;
struct snd_soc_pcm_runtime {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int stream; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_dma_buffer {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  area; } ;
struct TYPE_4__ {TYPE_1__ page_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 struct snd_dma_buffer* snd_pcm_get_dma_buf (struct snd_pcm_substream*) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int snd_sof_create_page_table (struct snd_sof_dev*,struct snd_dma_buffer*,int /*<<< orphan*/ ,size_t) ; 
 struct snd_sof_pcm* snd_sof_find_spcm_dai (struct snd_sof_dev*,struct snd_soc_pcm_runtime*) ; 

__attribute__((used)) static int create_page_table(struct snd_pcm_substream *substream,
			     unsigned char *dma_area, size_t size)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	struct snd_sof_pcm *spcm;
	struct snd_dma_buffer *dmab = snd_pcm_get_dma_buf(substream);
	int stream = substream->stream;

	spcm = snd_sof_find_spcm_dai(sdev, rtd);
	if (!spcm)
		return -EINVAL;

	return snd_sof_create_page_table(sdev, dmab,
		spcm->stream[stream].page_table.area, size);
}