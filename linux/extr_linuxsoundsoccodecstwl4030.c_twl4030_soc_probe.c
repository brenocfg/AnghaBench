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
struct twl4030_priv {int sysclk; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct twl4030_priv* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_set_drvdata (struct snd_soc_component*,struct twl4030_priv*) ; 
 int twl4030_audio_get_mclk () ; 
 int /*<<< orphan*/  twl4030_init_chip (struct snd_soc_component*) ; 

__attribute__((used)) static int twl4030_soc_probe(struct snd_soc_component *component)
{
	struct twl4030_priv *twl4030;

	twl4030 = devm_kzalloc(component->dev, sizeof(struct twl4030_priv),
			       GFP_KERNEL);
	if (!twl4030)
		return -ENOMEM;
	snd_soc_component_set_drvdata(component, twl4030);
	/* Set the defaults, and power up the codec */
	twl4030->sysclk = twl4030_audio_get_mclk() / 1000;

	twl4030_init_chip(component);

	return 0;
}