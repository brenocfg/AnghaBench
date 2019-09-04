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
struct TYPE_2__ {unsigned int* status; } ;
struct stm32_sai_sub_data {unsigned int spdif_frm_cnt; TYPE_1__ iec958; } ;
struct snd_soc_pcm_runtime {struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int dma_bytes; int channels; scalar_t__ dma_area; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned int SAI_IEC60958_BLOCK_FRAMES ; 
 int bytes_to_samples (struct snd_pcm_runtime*,unsigned long) ; 
 struct stm32_sai_sub_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_sai_pcm_process_spdif(struct snd_pcm_substream *substream,
				       int channel, unsigned long hwoff,
				       void *buf, unsigned long bytes)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct stm32_sai_sub_data *sai = dev_get_drvdata(cpu_dai->dev);
	int *ptr = (int *)(runtime->dma_area + hwoff +
			   channel * (runtime->dma_bytes / runtime->channels));
	ssize_t cnt = bytes_to_samples(runtime, bytes);
	unsigned int frm_cnt = sai->spdif_frm_cnt;
	unsigned int byte;
	unsigned int mask;

	do {
		*ptr = ((*ptr >> 8) & 0x00ffffff);

		/* Set channel status bit */
		byte = frm_cnt >> 3;
		mask = 1 << (frm_cnt - (byte << 3));
		if (sai->iec958.status[byte] & mask)
			*ptr |= 0x04000000;
		ptr++;

		if (!(cnt % 2))
			frm_cnt++;

		if (frm_cnt == SAI_IEC60958_BLOCK_FRAMES)
			frm_cnt = 0;
	} while (--cnt);
	sai->spdif_frm_cnt = frm_cnt;

	return 0;
}