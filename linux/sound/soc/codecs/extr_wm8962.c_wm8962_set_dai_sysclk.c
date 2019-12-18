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
struct wm8962_priv {int sysclk; unsigned int sysclk_rate; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WM8962_CLOCKING2 ; 
#define  WM8962_SYSCLK_FLL 129 
#define  WM8962_SYSCLK_MCLK 128 
 int /*<<< orphan*/  WM8962_SYSCLK_SRC_MASK ; 
 int WM8962_SYSCLK_SRC_SHIFT ; 
 struct wm8962_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8962_set_dai_sysclk(struct snd_soc_dai *dai, int clk_id,
				 unsigned int freq, int dir)
{
	struct snd_soc_component *component = dai->component;
	struct wm8962_priv *wm8962 = snd_soc_component_get_drvdata(component);
	int src;

	switch (clk_id) {
	case WM8962_SYSCLK_MCLK:
		wm8962->sysclk = WM8962_SYSCLK_MCLK;
		src = 0;
		break;
	case WM8962_SYSCLK_FLL:
		wm8962->sysclk = WM8962_SYSCLK_FLL;
		src = 1 << WM8962_SYSCLK_SRC_SHIFT;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, WM8962_CLOCKING2, WM8962_SYSCLK_SRC_MASK,
			    src);

	wm8962->sysclk_rate = freq;

	return 0;
}