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
struct snd_soc_dai {int dummy; } ;
struct s3c_pcm_info {int sclk_per_fs; } ;

/* Variables and functions */
 int EINVAL ; 
#define  S3C_PCM_SCLK_PER_FS 128 
 struct s3c_pcm_info* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int s3c_pcm_set_clkdiv(struct snd_soc_dai *cpu_dai,
						int div_id, int div)
{
	struct s3c_pcm_info *pcm = snd_soc_dai_get_drvdata(cpu_dai);

	switch (div_id) {
	case S3C_PCM_SCLK_PER_FS:
		pcm->sclk_per_fs = div;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}