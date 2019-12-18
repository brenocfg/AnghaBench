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
struct snd_soc_pcm_runtime {TYPE_1__* cpu_dai; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ MT2701_MEMIF_ULBT ; 
 int mt2701_afe_i2s_fs (unsigned int) ; 

__attribute__((used)) static int mt2701_memif_fs(struct snd_pcm_substream *substream,
			   unsigned int rate)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	int fs;

	if (rtd->cpu_dai->id != MT2701_MEMIF_ULBT)
		fs = mt2701_afe_i2s_fs(rate);
	else
		fs = (rate == 16000 ? 1 : 0);

	return fs;
}