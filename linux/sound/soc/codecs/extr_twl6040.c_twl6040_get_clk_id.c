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
struct twl6040_data {int pll_power_mode; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 struct twl6040_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

int twl6040_get_clk_id(struct snd_soc_component *component)
{
	struct twl6040_data *priv = snd_soc_component_get_drvdata(component);

	return priv->pll_power_mode;
}