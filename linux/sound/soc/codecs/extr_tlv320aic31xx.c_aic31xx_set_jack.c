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
struct snd_soc_jack {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct aic31xx_priv {int /*<<< orphan*/  regmap; struct snd_soc_jack* jack; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC31XX_HSDETECT ; 
 int /*<<< orphan*/  AIC31XX_HSD_ENABLE ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aic31xx_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int aic31xx_set_jack(struct snd_soc_component *component,
			    struct snd_soc_jack *jack, void *data)
{
	struct aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);

	aic31xx->jack = jack;

	/* Enable/Disable jack detection */
	regmap_write(aic31xx->regmap, AIC31XX_HSDETECT,
		     jack ? AIC31XX_HSD_ENABLE : 0);

	return 0;
}