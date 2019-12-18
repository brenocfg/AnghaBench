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
struct snd_soc_component {int dummy; } ;
struct rt5677_priv {int /*<<< orphan*/  reset_pin; int /*<<< orphan*/  pow_ldo2; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5677_RESET ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct rt5677_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void rt5677_remove(struct snd_soc_component *component)
{
	struct rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);

	regmap_write(rt5677->regmap, RT5677_RESET, 0x10ec);
	gpiod_set_value_cansleep(rt5677->pow_ldo2, 0);
	gpiod_set_value_cansleep(rt5677->reset_pin, 1);
}