#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_component {TYPE_1__* dev; } ;
struct cpcap_audio {int /*<<< orphan*/  vendor; int /*<<< orphan*/  regmap; struct snd_soc_component* component; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cpcap_audio_reset (struct snd_soc_component*,int) ; 
 int cpcap_get_vendor (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cpcap_audio* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_init_regmap (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_set_drvdata (struct snd_soc_component*,struct cpcap_audio*) ; 

__attribute__((used)) static int cpcap_soc_probe(struct snd_soc_component *component)
{
	struct cpcap_audio *cpcap;
	int err;

	cpcap = devm_kzalloc(component->dev, sizeof(*cpcap), GFP_KERNEL);
	if (!cpcap)
		return -ENOMEM;
	snd_soc_component_set_drvdata(component, cpcap);
	cpcap->component = component;

	cpcap->regmap = dev_get_regmap(component->dev->parent, NULL);
	if (!cpcap->regmap)
		return -ENODEV;
	snd_soc_component_init_regmap(component, cpcap->regmap);

	err = cpcap_get_vendor(component->dev, cpcap->regmap, &cpcap->vendor);
	if (err)
		return err;

	return cpcap_audio_reset(component, false);
}