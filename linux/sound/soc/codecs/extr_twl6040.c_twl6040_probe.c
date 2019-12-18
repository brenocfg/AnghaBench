#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct twl6040_data {scalar_t__ plug_irq; int /*<<< orphan*/  mutex; TYPE_1__ hs_jack; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_ONESHOT ; 
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct twl6040_data* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_force_bias_level (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_set_drvdata (struct snd_soc_component*,struct twl6040_data*) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6040_accessory_work ; 
 int /*<<< orphan*/  twl6040_audio_handler ; 
 int /*<<< orphan*/  twl6040_init_chip (struct snd_soc_component*) ; 

__attribute__((used)) static int twl6040_probe(struct snd_soc_component *component)
{
	struct twl6040_data *priv;
	struct platform_device *pdev = to_platform_device(component->dev);
	int ret = 0;

	priv = devm_kzalloc(component->dev, sizeof(*priv), GFP_KERNEL);
	if (priv == NULL)
		return -ENOMEM;

	snd_soc_component_set_drvdata(component, priv);

	priv->component = component;

	priv->plug_irq = platform_get_irq(pdev, 0);
	if (priv->plug_irq < 0)
		return priv->plug_irq;

	INIT_DELAYED_WORK(&priv->hs_jack.work, twl6040_accessory_work);

	mutex_init(&priv->mutex);

	ret = request_threaded_irq(priv->plug_irq, NULL,
					twl6040_audio_handler,
					IRQF_NO_SUSPEND | IRQF_ONESHOT,
					"twl6040_irq_plug", component);
	if (ret) {
		dev_err(component->dev, "PLUG IRQ request failed: %d\n", ret);
		return ret;
	}

	snd_soc_component_force_bias_level(component, SND_SOC_BIAS_STANDBY);
	twl6040_init_chip(component);

	return 0;
}