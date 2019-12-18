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
struct rt274_priv {int /*<<< orphan*/  jack_detect_work; TYPE_1__* i2c; struct snd_soc_component* component; } ;
struct TYPE_2__ {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  rt274_jack_detect_work ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rt274_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt274_probe(struct snd_soc_component *component)
{
	struct rt274_priv *rt274 = snd_soc_component_get_drvdata(component);

	rt274->component = component;

	if (rt274->i2c->irq) {
		INIT_DELAYED_WORK(&rt274->jack_detect_work,
					rt274_jack_detect_work);
		schedule_delayed_work(&rt274->jack_detect_work,
					msecs_to_jiffies(1250));
	}

	return 0;
}