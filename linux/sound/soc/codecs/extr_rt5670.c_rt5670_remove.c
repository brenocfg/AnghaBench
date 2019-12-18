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
struct rt5670_priv {int /*<<< orphan*/  hp_gpio; int /*<<< orphan*/  jack; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5670_RESET ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rt5670_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_jack_free_gpios (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt5670_remove(struct snd_soc_component *component)
{
	struct rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	regmap_write(rt5670->regmap, RT5670_RESET, 0);
	snd_soc_jack_free_gpios(rt5670->jack, 1, &rt5670->hp_gpio);
}