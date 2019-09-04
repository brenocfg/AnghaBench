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
struct TYPE_4__ {TYPE_1__* arizona; } ;
struct wm8998_priv {TYPE_2__ core; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dapm; } ;

/* Variables and functions */
 struct wm8998_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void wm8998_component_remove(struct snd_soc_component *component)
{
	struct wm8998_priv *priv = snd_soc_component_get_drvdata(component);

	priv->core.arizona->dapm = NULL;
}