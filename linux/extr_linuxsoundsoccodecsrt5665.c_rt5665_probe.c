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
struct snd_soc_component {int dummy; } ;
struct rt5665_priv {int /*<<< orphan*/  calibrate_work; struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rt5665_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5665_probe(struct snd_soc_component *component)
{
	struct rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);

	rt5665->component = component;

	schedule_delayed_work(&rt5665->calibrate_work, msecs_to_jiffies(100));

	return 0;
}