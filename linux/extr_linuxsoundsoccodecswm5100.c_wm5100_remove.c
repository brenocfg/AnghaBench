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
struct TYPE_2__ {scalar_t__ hp_pol; } ;
struct wm5100_priv {TYPE_1__ pdata; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 struct wm5100_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void wm5100_remove(struct snd_soc_component *component)
{
	struct wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);

	if (wm5100->pdata.hp_pol) {
		gpio_free(wm5100->pdata.hp_pol);
	}
}