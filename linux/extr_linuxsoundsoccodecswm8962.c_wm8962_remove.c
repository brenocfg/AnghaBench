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
struct wm8962_priv {int /*<<< orphan*/ * disable_nb; TYPE_1__* supplies; int /*<<< orphan*/  mic_work; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct wm8962_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8962_free_beep (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8962_free_gpio (struct snd_soc_component*) ; 

__attribute__((used)) static void wm8962_remove(struct snd_soc_component *component)
{
	struct wm8962_priv *wm8962 = snd_soc_component_get_drvdata(component);
	int i;

	cancel_delayed_work_sync(&wm8962->mic_work);

	wm8962_free_gpio(component);
	wm8962_free_beep(component);
	for (i = 0; i < ARRAY_SIZE(wm8962->supplies); i++)
		regulator_unregister_notifier(wm8962->supplies[i].consumer,
					      &wm8962->disable_nb[i]);
}