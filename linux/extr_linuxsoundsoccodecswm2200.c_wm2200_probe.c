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
struct wm2200_priv {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 struct wm2200_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int wm2200_probe(struct snd_soc_component *component)
{
	struct wm2200_priv *wm2200 = snd_soc_component_get_drvdata(component);

	wm2200->component = component;

	return 0;
}