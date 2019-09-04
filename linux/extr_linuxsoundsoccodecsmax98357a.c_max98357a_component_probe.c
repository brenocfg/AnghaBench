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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 struct gpio_desc* devm_gpiod_get_optional (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_set_drvdata (struct snd_soc_component*,struct gpio_desc*) ; 

__attribute__((used)) static int max98357a_component_probe(struct snd_soc_component *component)
{
	struct gpio_desc *sdmode;

	sdmode = devm_gpiod_get_optional(component->dev, "sdmode", GPIOD_OUT_LOW);
	if (IS_ERR(sdmode))
		return PTR_ERR(sdmode);

	snd_soc_component_set_drvdata(component, sdmode);

	return 0;
}