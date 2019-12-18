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
struct dmic {scalar_t__ wakeup_delay; scalar_t__ modeswitch_delay; int /*<<< orphan*/  gpio_en; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_MODESWITCH_DELAY ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_property_read_u32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct dmic* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ modeswitch_delay ; 
 int /*<<< orphan*/  snd_soc_component_set_drvdata (struct snd_soc_component*,struct dmic*) ; 
 scalar_t__ wakeup_delay ; 

__attribute__((used)) static int dmic_component_probe(struct snd_soc_component *component)
{
	struct dmic *dmic;

	dmic = devm_kzalloc(component->dev, sizeof(*dmic), GFP_KERNEL);
	if (!dmic)
		return -ENOMEM;

	dmic->gpio_en = devm_gpiod_get_optional(component->dev,
						"dmicen", GPIOD_OUT_LOW);
	if (IS_ERR(dmic->gpio_en))
		return PTR_ERR(dmic->gpio_en);

	device_property_read_u32(component->dev, "wakeup-delay-ms",
				 &dmic->wakeup_delay);
	device_property_read_u32(component->dev, "modeswitch-delay-ms",
				 &dmic->modeswitch_delay);
	if (wakeup_delay)
		dmic->wakeup_delay  = wakeup_delay;
	if (modeswitch_delay)
		dmic->modeswitch_delay  = modeswitch_delay;

	if (dmic->modeswitch_delay > MAX_MODESWITCH_DELAY)
		dmic->modeswitch_delay = MAX_MODESWITCH_DELAY;

	snd_soc_component_set_drvdata(component, dmic);

	return 0;
}