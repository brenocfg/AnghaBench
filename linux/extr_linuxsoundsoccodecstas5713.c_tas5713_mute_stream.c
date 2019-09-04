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
struct tas5713_priv {int /*<<< orphan*/  regmap; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAS5713_SOFT_MUTE ; 
 unsigned int TAS5713_SOFT_MUTE_ALL ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct tas5713_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int tas5713_mute_stream(struct snd_soc_dai *dai, int mute, int stream)
{
	unsigned int val = 0;

	struct tas5713_priv *tas5713;
	struct snd_soc_component *component = dai->component;
	tas5713 = snd_soc_component_get_drvdata(component);

	if (mute) {
		val = TAS5713_SOFT_MUTE_ALL;
	}

	return regmap_write(tas5713->regmap, TAS5713_SOFT_MUTE, val);
}