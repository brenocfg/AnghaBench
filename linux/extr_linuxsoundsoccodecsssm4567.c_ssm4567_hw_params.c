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
struct ssm4567 {int /*<<< orphan*/  regmap; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SSM4567_DAC_FS_128000_192000 ; 
 unsigned int SSM4567_DAC_FS_16000_24000 ; 
 unsigned int SSM4567_DAC_FS_32000_48000 ; 
 unsigned int SSM4567_DAC_FS_64000_96000 ; 
 unsigned int SSM4567_DAC_FS_8000_12000 ; 
 int /*<<< orphan*/  SSM4567_DAC_FS_MASK ; 
 int /*<<< orphan*/  SSM4567_REG_DAC_CTRL ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct ssm4567* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int ssm4567_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct ssm4567 *ssm4567 = snd_soc_component_get_drvdata(component);
	unsigned int rate = params_rate(params);
	unsigned int dacfs;

	if (rate >= 8000 && rate <= 12000)
		dacfs = SSM4567_DAC_FS_8000_12000;
	else if (rate >= 16000 && rate <= 24000)
		dacfs = SSM4567_DAC_FS_16000_24000;
	else if (rate >= 32000 && rate <= 48000)
		dacfs = SSM4567_DAC_FS_32000_48000;
	else if (rate >= 64000 && rate <= 96000)
		dacfs = SSM4567_DAC_FS_64000_96000;
	else if (rate >= 128000 && rate <= 192000)
		dacfs = SSM4567_DAC_FS_128000_192000;
	else
		return -EINVAL;

	return regmap_update_bits(ssm4567->regmap, SSM4567_REG_DAC_CTRL,
				SSM4567_DAC_FS_MASK, dacfs);
}