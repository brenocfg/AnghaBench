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
struct tas5086_private {int /*<<< orphan*/  supplies; int /*<<< orphan*/  gpio_nreset; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tas5086_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void tas5086_remove(struct snd_soc_component *component)
{
	struct tas5086_private *priv = snd_soc_component_get_drvdata(component);

	if (gpio_is_valid(priv->gpio_nreset))
		/* Set codec to the reset state */
		gpio_set_value(priv->gpio_nreset, 0);

	regulator_bulk_disable(ARRAY_SIZE(priv->supplies), priv->supplies);
}