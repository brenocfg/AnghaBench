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
struct pm860x_priv {int /*<<< orphan*/ * irq; int /*<<< orphan*/ * name; int /*<<< orphan*/  regmap; struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pm860x_priv*) ; 
 int /*<<< orphan*/  pm860x_component_handler ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pm860x_priv*) ; 
 struct pm860x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_init_regmap (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm860x_probe(struct snd_soc_component *component)
{
	struct pm860x_priv *pm860x = snd_soc_component_get_drvdata(component);
	int i, ret;

	pm860x->component = component;
	snd_soc_component_init_regmap(component,  pm860x->regmap);

	for (i = 0; i < 4; i++) {
		ret = request_threaded_irq(pm860x->irq[i], NULL,
					   pm860x_component_handler, IRQF_ONESHOT,
					   pm860x->name[i], pm860x);
		if (ret < 0) {
			dev_err(component->dev, "Failed to request IRQ!\n");
			goto out;
		}
	}

	return 0;

out:
	while (--i >= 0)
		free_irq(pm860x->irq[i], pm860x);
	return ret;
}