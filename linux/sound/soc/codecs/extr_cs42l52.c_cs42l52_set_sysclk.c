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
struct cs42l52_private {unsigned int sysclk; } ;

/* Variables and functions */
 unsigned int CS42L52_MAX_CLK ; 
 unsigned int CS42L52_MIN_CLK ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct cs42l52_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs42l52_set_sysclk(struct snd_soc_dai *codec_dai,
			int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct cs42l52_private *cs42l52 = snd_soc_component_get_drvdata(component);

	if ((freq >= CS42L52_MIN_CLK) && (freq <= CS42L52_MAX_CLK)) {
		cs42l52->sysclk = freq;
	} else {
		dev_err(component->dev, "Invalid freq parameter\n");
		return -EINVAL;
	}
	return 0;
}