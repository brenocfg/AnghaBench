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
struct snd_soc_component {int dummy; } ;
struct rt5645_priv {TYPE_1__* eq_param; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int RT5645_HWEQ_NUM ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt5645_validate_hweq (int /*<<< orphan*/ ) ; 
 struct rt5645_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5645_enable_hweq(struct snd_soc_component *component)
{
	struct rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	int i;

	for (i = 0; i < RT5645_HWEQ_NUM; i++) {
		if (rt5645_validate_hweq(rt5645->eq_param[i].reg))
			regmap_write(rt5645->regmap, rt5645->eq_param[i].reg,
					rt5645->eq_param[i].val);
		else
			break;
	}

	return 0;
}