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
typedef  int /*<<< orphan*/  u16 ;
struct wm8961_priv {unsigned int sysclk; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WM8961_CLOCKING1 ; 
 int /*<<< orphan*/  WM8961_MCLKDIV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct wm8961_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8961_set_sysclk(struct snd_soc_dai *dai, int clk_id,
			     unsigned int freq,
			     int dir)
{
	struct snd_soc_component *component = dai->component;
	struct wm8961_priv *wm8961 = snd_soc_component_get_drvdata(component);
	u16 reg = snd_soc_component_read32(component, WM8961_CLOCKING1);

	if (freq > 33000000) {
		dev_err(component->dev, "MCLK must be <33MHz\n");
		return -EINVAL;
	}

	if (freq > 16500000) {
		dev_dbg(component->dev, "Using MCLK/2 for %dHz MCLK\n", freq);
		reg |= WM8961_MCLKDIV;
		freq /= 2;
	} else {
		dev_dbg(component->dev, "Using MCLK/1 for %dHz MCLK\n", freq);
		reg &= ~WM8961_MCLKDIV;
	}

	snd_soc_component_write(component, WM8961_CLOCKING1, reg);

	wm8961->sysclk = freq;

	return 0;
}