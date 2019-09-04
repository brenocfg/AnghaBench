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
struct twl4030_priv {struct twl4030_codec_data* pdata; } ;
struct twl4030_codec_data {int /*<<< orphan*/  hs_extmute_gpio; scalar_t__ hs_extmute; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct twl4030_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void twl4030_soc_remove(struct snd_soc_component *component)
{
	struct twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	struct twl4030_codec_data *pdata = twl4030->pdata;

	if (pdata && pdata->hs_extmute && gpio_is_valid(pdata->hs_extmute_gpio))
		gpio_free(pdata->hs_extmute_gpio);
}