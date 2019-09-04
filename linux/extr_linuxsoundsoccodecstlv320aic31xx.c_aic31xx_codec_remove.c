#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_component {int dummy; } ;
struct aic31xx_priv {TYPE_1__* disable_nb; TYPE_2__* supplies; } ;
struct TYPE_4__ {int /*<<< orphan*/  consumer; } ;
struct TYPE_3__ {int /*<<< orphan*/  nb; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  regulator_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct aic31xx_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void aic31xx_codec_remove(struct snd_soc_component *component)
{
	struct aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);
	int i;

	for (i = 0; i < ARRAY_SIZE(aic31xx->supplies); i++)
		regulator_unregister_notifier(aic31xx->supplies[i].consumer,
					      &aic31xx->disable_nb[i].nb);
}