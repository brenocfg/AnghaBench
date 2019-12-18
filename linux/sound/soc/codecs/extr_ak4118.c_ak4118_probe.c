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
struct ak4118_priv {int /*<<< orphan*/  regmap; int /*<<< orphan*/  reset; struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4118_REG_INT1_MASK ; 
 int /*<<< orphan*/  AK4118_REG_RX_DETECT ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ak4118_iec958_controls ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ak4118_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int ak4118_probe(struct snd_soc_component *component)
{
	struct ak4118_priv *ak4118 = snd_soc_component_get_drvdata(component);
	int ret = 0;

	ak4118->component = component;

	/* release reset */
	gpiod_set_value(ak4118->reset, 0);

	/* unmask all int1 sources */
	ret = regmap_write(ak4118->regmap, AK4118_REG_INT1_MASK, 0x00);
	if (ret < 0) {
		dev_err(component->dev,
			"failed to write regmap 0x%x 0x%x: %d\n",
			AK4118_REG_INT1_MASK, 0x00, ret);
		return ret;
	}

	/* rx detect enable on all channels */
	ret = regmap_write(ak4118->regmap, AK4118_REG_RX_DETECT, 0xff);
	if (ret < 0) {
		dev_err(component->dev,
			"failed to write regmap 0x%x 0x%x: %d\n",
			AK4118_REG_RX_DETECT, 0xff, ret);
		return ret;
	}

	ret = snd_soc_add_component_controls(component, ak4118_iec958_controls,
					 ARRAY_SIZE(ak4118_iec958_controls));
	if (ret) {
		dev_err(component->dev,
			"failed to add component kcontrols: %d\n", ret);
		return ret;
	}

	return 0;
}