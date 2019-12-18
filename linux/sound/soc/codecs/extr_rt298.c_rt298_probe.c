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
struct rt298_priv {int /*<<< orphan*/  jack_detect_work; int /*<<< orphan*/  regmap; TYPE_1__* i2c; struct snd_soc_component* component; } ;
struct TYPE_2__ {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT298_IRQ_CTRL ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rt298_jack_detect_work ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rt298_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt298_probe(struct snd_soc_component *component)
{
	struct rt298_priv *rt298 = snd_soc_component_get_drvdata(component);

	rt298->component = component;

	if (rt298->i2c->irq) {
		regmap_update_bits(rt298->regmap,
					RT298_IRQ_CTRL, 0x2, 0x2);

		INIT_DELAYED_WORK(&rt298->jack_detect_work,
					rt298_jack_detect_work);
		schedule_delayed_work(&rt298->jack_detect_work,
					msecs_to_jiffies(1250));
	}

	return 0;
}