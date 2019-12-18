#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct cs4265_private {unsigned int sysclk; } ;
struct TYPE_3__ {unsigned int mclk; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* clk_map_table ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct cs4265_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs4265_set_sysclk(struct snd_soc_dai *codec_dai, int clk_id,
			unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct cs4265_private *cs4265 = snd_soc_component_get_drvdata(component);
	int i;

	if (clk_id != 0) {
		dev_err(component->dev, "Invalid clk_id %d\n", clk_id);
		return -EINVAL;
	}
	for (i = 0; i < ARRAY_SIZE(clk_map_table); i++) {
		if (clk_map_table[i].mclk == freq) {
			cs4265->sysclk = freq;
			return 0;
		}
	}
	cs4265->sysclk = 0;
	dev_err(component->dev, "Invalid freq parameter %d\n", freq);
	return -EINVAL;
}