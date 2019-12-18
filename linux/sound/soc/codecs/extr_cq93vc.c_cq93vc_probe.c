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
struct snd_soc_component {TYPE_1__* dev; } ;
struct davinci_vc {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {struct davinci_vc* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_soc_component_init_regmap (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cq93vc_probe(struct snd_soc_component *component)
{
	struct davinci_vc *davinci_vc = component->dev->platform_data;

	snd_soc_component_init_regmap(component, davinci_vc->regmap);

	return 0;
}