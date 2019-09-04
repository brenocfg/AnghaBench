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
struct tas5086_private {scalar_t__ rate; int /*<<< orphan*/  regmap; scalar_t__ deemph; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  TAS5086_DEEMPH_MASK ; 
 int /*<<< orphan*/  TAS5086_SYS_CONTROL_1 ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct tas5086_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 scalar_t__* tas5086_deemph ; 

__attribute__((used)) static int tas5086_set_deemph(struct snd_soc_component *component)
{
	struct tas5086_private *priv = snd_soc_component_get_drvdata(component);
	int i, val = 0;

	if (priv->deemph) {
		for (i = 0; i < ARRAY_SIZE(tas5086_deemph); i++) {
			if (tas5086_deemph[i] == priv->rate) {
				val = i;
				break;
			}
		}
	}

	return regmap_update_bits(priv->regmap, TAS5086_SYS_CONTROL_1,
				  TAS5086_DEEMPH_MASK, val);
}