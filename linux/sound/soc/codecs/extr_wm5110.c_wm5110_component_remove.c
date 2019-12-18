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
struct TYPE_4__ {TYPE_1__* arizona; int /*<<< orphan*/ * adsp; } ;
struct wm5110_priv {TYPE_2__ core; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dapm; } ;

/* Variables and functions */
 int WM5110_NUM_ADSP ; 
 struct wm5110_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm_adsp2_component_remove (int /*<<< orphan*/ *,struct snd_soc_component*) ; 

__attribute__((used)) static void wm5110_component_remove(struct snd_soc_component *component)
{
	struct wm5110_priv *priv = snd_soc_component_get_drvdata(component);
	int i;

	for (i = 0; i < WM5110_NUM_ADSP; ++i)
		wm_adsp2_component_remove(&priv->core.adsp[i], component);

	priv->core.arizona->dapm = NULL;
}