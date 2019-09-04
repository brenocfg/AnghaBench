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
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct ak5386_priv {int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 struct ak5386_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int ak5386_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct ak5386_priv *priv = snd_soc_component_get_drvdata(component);

	/*
	 * From the datasheet:
	 *
	 * All external clocks (MCLK, SCLK and LRCK) must be present unless
	 * PDN pin = “L”. If these clocks are not provided, the AK5386 may
	 * draw excess current due to its use of internal dynamically
	 * refreshed logic. If the external clocks are not present, place
	 * the AK5386 in power-down mode (PDN pin = “L”).
	 */

	if (gpio_is_valid(priv->reset_gpio))
		gpio_set_value(priv->reset_gpio, 1);

	return 0;
}