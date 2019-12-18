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
struct tas5086_private {int /*<<< orphan*/  regmap; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAS5086_SOFT_MUTE ; 
 unsigned int TAS5086_SOFT_MUTE_ALL ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct tas5086_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int tas5086_mute_stream(struct snd_soc_dai *dai, int mute, int stream)
{
	struct snd_soc_component *component = dai->component;
	struct tas5086_private *priv = snd_soc_component_get_drvdata(component);
	unsigned int val = 0;

	if (mute)
		val = TAS5086_SOFT_MUTE_ALL;

	return regmap_write(priv->regmap, TAS5086_SOFT_MUTE, val);
}