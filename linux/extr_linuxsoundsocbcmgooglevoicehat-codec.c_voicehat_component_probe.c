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
struct voicehat_priv {int /*<<< orphan*/  enable_sdmode_work; int /*<<< orphan*/  sdmode_gpio; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct voicehat_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  voicehat_enable_sdmode_work ; 

__attribute__((used)) static int voicehat_component_probe(struct snd_soc_component *component)
{
	struct voicehat_priv *voicehat =
				snd_soc_component_get_drvdata(component);

	voicehat->sdmode_gpio = devm_gpiod_get(component->dev, "sdmode",
					       GPIOD_OUT_LOW);
	if (IS_ERR(voicehat->sdmode_gpio)) {
		dev_err(component->dev, "Unable to allocate GPIO pin\n");
		return PTR_ERR(voicehat->sdmode_gpio);
	}

	INIT_DELAYED_WORK(&voicehat->enable_sdmode_work,
			  voicehat_enable_sdmode_work);
	return 0;
}