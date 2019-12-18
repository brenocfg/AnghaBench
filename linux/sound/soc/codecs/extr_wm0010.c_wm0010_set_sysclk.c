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
struct wm0010_priv {unsigned int sysclk; int /*<<< orphan*/  pll_clkctrl1; scalar_t__ max_spi_freq; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_3__ {unsigned int max_sysclk; int /*<<< orphan*/  pll_clkctrl1; scalar_t__ max_pll_spi_speed; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* pll_clock_map ; 
 struct wm0010_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int wm0010_set_sysclk(struct snd_soc_component *component, int source,
			     int clk_id, unsigned int freq, int dir)
{
	struct wm0010_priv *wm0010 = snd_soc_component_get_drvdata(component);
	unsigned int i;

	wm0010->sysclk = freq;

	if (freq < pll_clock_map[ARRAY_SIZE(pll_clock_map)-1].max_sysclk) {
		wm0010->max_spi_freq = 0;
	} else {
		for (i = 0; i < ARRAY_SIZE(pll_clock_map); i++)
			if (freq >= pll_clock_map[i].max_sysclk) {
				wm0010->max_spi_freq = pll_clock_map[i].max_pll_spi_speed;
				wm0010->pll_clkctrl1 = pll_clock_map[i].pll_clkctrl1;
				break;
			}
	}

	return 0;
}