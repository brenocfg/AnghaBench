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
struct aic3x_priv {TYPE_1__* disable_nb; TYPE_2__* supplies; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  consumer; } ;
struct TYPE_3__ {int /*<<< orphan*/  nb; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct aic3x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void aic3x_remove(struct snd_soc_component *component)
{
	struct aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);
	int i;

	list_del(&aic3x->list);
	for (i = 0; i < ARRAY_SIZE(aic3x->supplies); i++)
		regulator_unregister_notifier(aic3x->supplies[i].consumer,
					      &aic3x->disable_nb[i].nb);
}