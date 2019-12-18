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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAS5720_DIGITAL_CTRL2_REG ; 
 int /*<<< orphan*/  TAS5720_MUTE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tas5720_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_component *component = dai->component;
	int ret;

	ret = snd_soc_component_update_bits(component, TAS5720_DIGITAL_CTRL2_REG,
				  TAS5720_MUTE, mute ? TAS5720_MUTE : 0);
	if (ret < 0) {
		dev_err(component->dev, "error (un-)muting device: %d\n", ret);
		return ret;
	}

	return 0;
}