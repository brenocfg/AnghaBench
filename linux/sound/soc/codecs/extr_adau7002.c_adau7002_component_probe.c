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
struct adau7002_priv {int /*<<< orphan*/  wakeup_delay; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  device_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct adau7002_priv* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_set_drvdata (struct snd_soc_component*,struct adau7002_priv*) ; 

__attribute__((used)) static int adau7002_component_probe(struct snd_soc_component *component)
{
	struct adau7002_priv *adau7002;

	adau7002 = devm_kzalloc(component->dev, sizeof(*adau7002),
				GFP_KERNEL);
	if (!adau7002)
		return -ENOMEM;

	device_property_read_u32(component->dev, "wakeup-delay-ms",
				 &adau7002->wakeup_delay);

	snd_soc_component_set_drvdata(component, adau7002);

	return 0;
}