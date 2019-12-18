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
struct wm9081_priv {int sysclk_source; unsigned int mclk_rate; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  WM9081_SYSCLK_FLL_MCLK 129 
#define  WM9081_SYSCLK_MCLK 128 
 struct wm9081_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int wm9081_set_sysclk(struct snd_soc_component *component, int clk_id,
			     int source, unsigned int freq, int dir)
{
	struct wm9081_priv *wm9081 = snd_soc_component_get_drvdata(component);

	switch (clk_id) {
	case WM9081_SYSCLK_MCLK:
	case WM9081_SYSCLK_FLL_MCLK:
		wm9081->sysclk_source = clk_id;
		wm9081->mclk_rate = freq;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}