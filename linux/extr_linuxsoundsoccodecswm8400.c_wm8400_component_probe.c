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
typedef  int u16 ;
struct wm8400_priv {struct wm8400* wm8400; } ;
struct wm8400 {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WM8400_CODEC_ENA ; 
 int WM8400_IPVU ; 
 int /*<<< orphan*/  WM8400_LEFT_LINE_INPUT_1_2_VOLUME ; 
 int /*<<< orphan*/  WM8400_LEFT_OUTPUT_VOLUME ; 
 int /*<<< orphan*/  WM8400_POWER_MANAGEMENT_1 ; 
 int /*<<< orphan*/  WM8400_RIGHT_LINE_INPUT_1_2_VOLUME ; 
 int /*<<< orphan*/  WM8400_RIGHT_OUTPUT_VOLUME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct wm8400* dev_get_platdata (int /*<<< orphan*/ ) ; 
 struct wm8400_priv* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * power ; 
 int /*<<< orphan*/  snd_soc_component_init_regmap (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_set_drvdata (struct snd_soc_component*,struct wm8400_priv*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8400_component_reset (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8400_component_probe(struct snd_soc_component *component)
{
	struct wm8400 *wm8400 = dev_get_platdata(component->dev);
	struct wm8400_priv *priv;
	int ret;
	u16 reg;

	priv = devm_kzalloc(component->dev, sizeof(struct wm8400_priv),
			    GFP_KERNEL);
	if (priv == NULL)
		return -ENOMEM;

	snd_soc_component_init_regmap(component, wm8400->regmap);
	snd_soc_component_set_drvdata(component, priv);
	priv->wm8400 = wm8400;

	ret = devm_regulator_bulk_get(wm8400->dev,
				 ARRAY_SIZE(power), &power[0]);
	if (ret != 0) {
		dev_err(component->dev, "Failed to get regulators: %d\n", ret);
		return ret;
	}

	wm8400_component_reset(component);

	reg = snd_soc_component_read32(component, WM8400_POWER_MANAGEMENT_1);
	snd_soc_component_write(component, WM8400_POWER_MANAGEMENT_1, reg | WM8400_CODEC_ENA);

	/* Latch volume update bits */
	reg = snd_soc_component_read32(component, WM8400_LEFT_LINE_INPUT_1_2_VOLUME);
	snd_soc_component_write(component, WM8400_LEFT_LINE_INPUT_1_2_VOLUME,
		     reg & WM8400_IPVU);
	reg = snd_soc_component_read32(component, WM8400_RIGHT_LINE_INPUT_1_2_VOLUME);
	snd_soc_component_write(component, WM8400_RIGHT_LINE_INPUT_1_2_VOLUME,
		     reg & WM8400_IPVU);

	snd_soc_component_write(component, WM8400_LEFT_OUTPUT_VOLUME, 0x50 | (1<<8));
	snd_soc_component_write(component, WM8400_RIGHT_OUTPUT_VOLUME, 0x50 | (1<<8));

	return 0;
}