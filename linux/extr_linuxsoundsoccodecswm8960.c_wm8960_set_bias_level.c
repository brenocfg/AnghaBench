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
struct wm8960_priv {int (* set_bias_level ) (struct snd_soc_component*,int) ;} ;
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 struct wm8960_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int stub1 (struct snd_soc_component*,int) ; 

__attribute__((used)) static int wm8960_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);

	return wm8960->set_bias_level(component, level);
}