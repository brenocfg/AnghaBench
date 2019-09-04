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
struct wm8995_priv {TYPE_1__* supplies; int /*<<< orphan*/ * disable_nb; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  regulator_bulk_free (int,TYPE_1__*) ; 
 int /*<<< orphan*/  regulator_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct wm8995_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void wm8995_remove(struct snd_soc_component *component)
{
	struct wm8995_priv *wm8995;
	int i;

	wm8995 = snd_soc_component_get_drvdata(component);

	for (i = 0; i < ARRAY_SIZE(wm8995->supplies); ++i)
		regulator_unregister_notifier(wm8995->supplies[i].consumer,
					      &wm8995->disable_nb[i]);

	regulator_bulk_free(ARRAY_SIZE(wm8995->supplies), wm8995->supplies);
}