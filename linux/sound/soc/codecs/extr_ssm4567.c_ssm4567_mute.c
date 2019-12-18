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
struct snd_soc_dai {int /*<<< orphan*/  component; } ;

/* Variables and functions */
 unsigned int SSM4567_DAC_MUTE ; 
 int /*<<< orphan*/  SSM4567_REG_DAC_CTRL ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct ssm4567* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssm4567_mute(struct snd_soc_dai *dai, int mute)
{
	struct ssm4567 *ssm4567 = snd_soc_component_get_drvdata(dai->component);
	unsigned int val;

	val = mute ? SSM4567_DAC_MUTE : 0;
	return regmap_update_bits(ssm4567->regmap, SSM4567_REG_DAC_CTRL,
			SSM4567_DAC_MUTE, val);
}