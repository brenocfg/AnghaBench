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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; struct snd_soc_pcm_runtime* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int snd_pcm_hw_constraint_msbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void soc_pcm_set_msb(struct snd_pcm_substream *substream, int bits)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	int ret;

	if (!bits)
		return;

	ret = snd_pcm_hw_constraint_msbits(substream->runtime, 0, 0, bits);
	if (ret != 0)
		dev_warn(rtd->dev, "ASoC: Failed to set MSB %d: %d\n",
				 bits, ret);
}