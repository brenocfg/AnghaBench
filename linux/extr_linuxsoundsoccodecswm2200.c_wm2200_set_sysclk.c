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
struct wm2200_priv {unsigned int sysclk; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  WM2200_CLKSRC_BCLK1 132 
#define  WM2200_CLKSRC_FLL 131 
#define  WM2200_CLKSRC_MCLK1 130 
#define  WM2200_CLKSRC_MCLK2 129 
#define  WM2200_CLK_SYSCLK 128 
 int /*<<< orphan*/  WM2200_CLOCKING_3 ; 
 int WM2200_SYSCLK_FREQ_MASK ; 
 int WM2200_SYSCLK_FREQ_SHIFT ; 
 int WM2200_SYSCLK_SRC_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct wm2200_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm2200_set_sysclk(struct snd_soc_component *component, int clk_id,
			     int source, unsigned int freq, int dir)
{
	struct wm2200_priv *wm2200 = snd_soc_component_get_drvdata(component);
	int fval;

	switch (clk_id) {
	case WM2200_CLK_SYSCLK:
		break;

	default:
		dev_err(component->dev, "Unknown clock %d\n", clk_id);
		return -EINVAL;
	}

	switch (source) {
	case WM2200_CLKSRC_MCLK1:
	case WM2200_CLKSRC_MCLK2:
	case WM2200_CLKSRC_FLL:
	case WM2200_CLKSRC_BCLK1:
		break;
	default:
		dev_err(component->dev, "Invalid source %d\n", source);
		return -EINVAL;
	}

	switch (freq) {
	case 22579200:
	case 24576000:
		fval = 2;
		break;
	default:
		dev_err(component->dev, "Invalid clock rate: %d\n", freq);
		return -EINVAL;
	}

	/* TODO: Check if MCLKs are in use and enable/disable pulls to
	 * match.
	 */

	snd_soc_component_update_bits(component, WM2200_CLOCKING_3, WM2200_SYSCLK_FREQ_MASK |
			    WM2200_SYSCLK_SRC_MASK,
			    fval << WM2200_SYSCLK_FREQ_SHIFT | source);

	wm2200->sysclk = freq;

	return 0;
}