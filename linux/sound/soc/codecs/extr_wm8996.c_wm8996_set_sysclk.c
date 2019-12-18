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
struct wm8996_priv {unsigned int sysclk; int sysclk_src; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WM8996_AIF_CLOCKING_1 ; 
 int /*<<< orphan*/  WM8996_AIF_RATE ; 
 int /*<<< orphan*/  WM8996_CLOCKING_1 ; 
 int /*<<< orphan*/  WM8996_CONTROL_INTERFACE_1 ; 
 int WM8996_LFCLK_ENA ; 
 int WM8996_REG_SYNC ; 
 int WM8996_SYSCLK_DIV ; 
 int WM8996_SYSCLK_DIV_MASK ; 
 int WM8996_SYSCLK_ENA ; 
#define  WM8996_SYSCLK_FLL 130 
#define  WM8996_SYSCLK_MCLK1 129 
#define  WM8996_SYSCLK_MCLK2 128 
 int WM8996_SYSCLK_RATE ; 
 int WM8996_SYSCLK_SRC_MASK ; 
 int WM8996_SYSCLK_SRC_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 struct wm8996_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wm8996_update_bclk (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8996_set_sysclk(struct snd_soc_dai *dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = dai->component;
	struct wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	int lfclk = 0;
	int ratediv = 0;
	int sync = WM8996_REG_SYNC;
	int src;
	int old;

	if (freq == wm8996->sysclk && clk_id == wm8996->sysclk_src)
		return 0;

	/* Disable SYSCLK while we reconfigure */
	old = snd_soc_component_read32(component, WM8996_AIF_CLOCKING_1) & WM8996_SYSCLK_ENA;
	snd_soc_component_update_bits(component, WM8996_AIF_CLOCKING_1,
			    WM8996_SYSCLK_ENA, 0);

	switch (clk_id) {
	case WM8996_SYSCLK_MCLK1:
		wm8996->sysclk = freq;
		src = 0;
		break;
	case WM8996_SYSCLK_MCLK2:
		wm8996->sysclk = freq;
		src = 1;
		break;
	case WM8996_SYSCLK_FLL:
		wm8996->sysclk = freq;
		src = 2;
		break;
	default:
		dev_err(component->dev, "Unsupported clock source %d\n", clk_id);
		return -EINVAL;
	}

	switch (wm8996->sysclk) {
	case 5644800:
	case 6144000:
		snd_soc_component_update_bits(component, WM8996_AIF_RATE,
				    WM8996_SYSCLK_RATE, 0);
		break;
	case 22579200:
	case 24576000:
		ratediv = WM8996_SYSCLK_DIV;
		wm8996->sysclk /= 2;
		/* fall through */
	case 11289600:
	case 12288000:
		snd_soc_component_update_bits(component, WM8996_AIF_RATE,
				    WM8996_SYSCLK_RATE, WM8996_SYSCLK_RATE);
		break;
	case 32000:
	case 32768:
		lfclk = WM8996_LFCLK_ENA;
		sync = 0;
		break;
	default:
		dev_warn(component->dev, "Unsupported clock rate %dHz\n",
			 wm8996->sysclk);
		return -EINVAL;
	}

	wm8996_update_bclk(component);

	snd_soc_component_update_bits(component, WM8996_AIF_CLOCKING_1,
			    WM8996_SYSCLK_SRC_MASK | WM8996_SYSCLK_DIV_MASK,
			    src << WM8996_SYSCLK_SRC_SHIFT | ratediv);
	snd_soc_component_update_bits(component, WM8996_CLOCKING_1, WM8996_LFCLK_ENA, lfclk);
	snd_soc_component_update_bits(component, WM8996_CONTROL_INTERFACE_1,
			    WM8996_REG_SYNC, sync);
	snd_soc_component_update_bits(component, WM8996_AIF_CLOCKING_1,
			    WM8996_SYSCLK_ENA, old);

	wm8996->sysclk_src = clk_id;

	return 0;
}