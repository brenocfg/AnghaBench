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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct fsl_asrc_pair* private_data; } ;
struct fsl_asrc_pair {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_asrc_release_pair (struct fsl_asrc_pair*) ; 

__attribute__((used)) static int fsl_asrc_dai_hw_free(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct fsl_asrc_pair *pair = runtime->private_data;

	if (pair)
		fsl_asrc_release_pair(pair);

	return 0;
}