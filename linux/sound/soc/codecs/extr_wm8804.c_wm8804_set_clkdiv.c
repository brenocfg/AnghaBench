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
struct wm8804_priv {int mclk_div; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  WM8804_CLKOUT_DIV 129 
#define  WM8804_MCLK_DIV 128 
 int /*<<< orphan*/  WM8804_PLL5 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct wm8804_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm8804_set_clkdiv(struct snd_soc_dai *dai,
			     int div_id, int div)
{
	struct snd_soc_component *component;
	struct wm8804_priv *wm8804;

	component = dai->component;
	switch (div_id) {
	case WM8804_CLKOUT_DIV:
		snd_soc_component_update_bits(component, WM8804_PLL5, 0x30,
				    (div & 0x3) << 4);
		break;
	case WM8804_MCLK_DIV:
		wm8804 = snd_soc_component_get_drvdata(component);
		wm8804->mclk_div = div;
		break;
	default:
		dev_err(dai->dev, "Unknown clock divider: %d\n", div_id);
		return -EINVAL;
	}
	return 0;
}