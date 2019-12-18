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
struct wm5100_priv {int sysclk; int asyncclk; int* aif_async; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
#define  WM5100_CLKSRC_ASYNCCLK 138 
#define  WM5100_CLKSRC_MCLK1 137 
#define  WM5100_CLKSRC_MCLK2 136 
#define  WM5100_CLKSRC_SYSCLK 135 
#define  WM5100_CLK_32KHZ 134 
 int WM5100_CLK_32K_SRC_MASK ; 
#define  WM5100_CLK_AIF1 133 
#define  WM5100_CLK_AIF2 132 
#define  WM5100_CLK_AIF3 131 
#define  WM5100_CLK_ASYNCCLK 130 
#define  WM5100_CLK_OPCLK 129 
#define  WM5100_CLK_SYSCLK 128 
 int WM5100_CLOCKING_1 ; 
 int WM5100_CLOCKING_3 ; 
 int WM5100_CLOCKING_7 ; 
 int WM5100_MISC_GPIO_1 ; 
 int WM5100_OPCLK_SEL_MASK ; 
 int WM5100_SYSCLK_FREQ_MASK ; 
 int WM5100_SYSCLK_FREQ_SHIFT ; 
 int WM5100_SYSCLK_SRC_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 struct wm5100_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int,int) ; 
 int wm5100_alloc_sr (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  wm5100_free_sr (struct snd_soc_component*,int) ; 

__attribute__((used)) static int wm5100_set_sysclk(struct snd_soc_component *component, int clk_id,
			     int source, unsigned int freq, int dir)
{
	struct wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);
	int *rate_store;
	int fval, audio_rate, ret, reg;

	switch (clk_id) {
	case WM5100_CLK_SYSCLK:
		reg = WM5100_CLOCKING_3;
		rate_store = &wm5100->sysclk;
		break;
	case WM5100_CLK_ASYNCCLK:
		reg = WM5100_CLOCKING_7;
		rate_store = &wm5100->asyncclk;
		break;
	case WM5100_CLK_32KHZ:
		/* The 32kHz clock is slightly different to the others */
		switch (source) {
		case WM5100_CLKSRC_MCLK1:
		case WM5100_CLKSRC_MCLK2:
		case WM5100_CLKSRC_SYSCLK:
			snd_soc_component_update_bits(component, WM5100_CLOCKING_1,
					    WM5100_CLK_32K_SRC_MASK,
					    source);
			break;
		default:
			return -EINVAL;
		}
		return 0;

	case WM5100_CLK_AIF1:
	case WM5100_CLK_AIF2:
	case WM5100_CLK_AIF3:
		/* Not real clocks, record which clock domain they're in */
		switch (source) {
		case WM5100_CLKSRC_SYSCLK:
			wm5100->aif_async[clk_id - 1] = false;
			break;
		case WM5100_CLKSRC_ASYNCCLK:
			wm5100->aif_async[clk_id - 1] = true;
			break;
		default:
			dev_err(component->dev, "Invalid source %d\n", source);
			return -EINVAL;
		}	
		return 0;

	case WM5100_CLK_OPCLK:
		switch (freq) {
		case 5644800:
		case 6144000:
			snd_soc_component_update_bits(component, WM5100_MISC_GPIO_1,
					    WM5100_OPCLK_SEL_MASK, 0);
			break;
		case 11289600:
		case 12288000:
			snd_soc_component_update_bits(component, WM5100_MISC_GPIO_1,
					    WM5100_OPCLK_SEL_MASK, 0);
			break;
		case 22579200:
		case 24576000:
			snd_soc_component_update_bits(component, WM5100_MISC_GPIO_1,
					    WM5100_OPCLK_SEL_MASK, 0);
			break;
		default:
			dev_err(component->dev, "Unsupported OPCLK %dHz\n",
				freq);
			return -EINVAL;
		}
		return 0;

	default:
		dev_err(component->dev, "Unknown clock %d\n", clk_id);
		return -EINVAL;
	}

	switch (source) {
	case WM5100_CLKSRC_SYSCLK:
	case WM5100_CLKSRC_ASYNCCLK:
		dev_err(component->dev, "Invalid source %d\n", source);
		return -EINVAL;
	}

	switch (freq) {
	case 5644800:
	case 6144000:
		fval = 0;
		break;
	case 11289600:
	case 12288000:
		fval = 1;
		break;
	case 22579200:
	case 24576000:
		fval = 2;
		break;
	default:
		dev_err(component->dev, "Invalid clock rate: %d\n", freq);
		return -EINVAL;
	}

	switch (freq) {
	case 5644800:
	case 11289600:
	case 22579200:
		audio_rate = 44100;
		break;

	case 6144000:
	case 12288000:
	case 24576000:
		audio_rate = 48000;
		break;

	default:
		BUG();
		audio_rate = 0;
		break;
	}

	/* TODO: Check if MCLKs are in use and enable/disable pulls to
	 * match.
	 */

	snd_soc_component_update_bits(component, reg, WM5100_SYSCLK_FREQ_MASK |
			    WM5100_SYSCLK_SRC_MASK,
			    fval << WM5100_SYSCLK_FREQ_SHIFT | source);

	/* If this is SYSCLK then configure the clock rate for the
	 * internal audio functions to the natural sample rate for
	 * this clock rate.
	 */
	if (clk_id == WM5100_CLK_SYSCLK) {
		dev_dbg(component->dev, "Setting primary audio rate to %dHz",
			audio_rate);
		if (0 && *rate_store)
			wm5100_free_sr(component, audio_rate);
		ret = wm5100_alloc_sr(component, audio_rate);
		if (ret != 0)
			dev_warn(component->dev, "Primary audio slot is %d\n",
				 ret);
	}

	*rate_store = freq;

	return 0;
}