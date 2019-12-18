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
struct pm8916_wcd_analog_priv {int /*<<< orphan*/  supplies; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDC_D_CDC_RST_CTL ; 
 int /*<<< orphan*/  RST_CTL_DIG_SW_RST_N_MASK ; 
 struct pm8916_wcd_analog_priv* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pm8916_wcd_analog_remove(struct snd_soc_component *component)
{
	struct pm8916_wcd_analog_priv *priv = dev_get_drvdata(component->dev);

	snd_soc_component_update_bits(component, CDC_D_CDC_RST_CTL,
			    RST_CTL_DIG_SW_RST_N_MASK, 0);

	regulator_bulk_disable(ARRAY_SIZE(priv->supplies),
				      priv->supplies);
}