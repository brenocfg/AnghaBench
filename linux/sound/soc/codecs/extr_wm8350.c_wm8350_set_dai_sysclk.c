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
typedef  int u16 ;
struct wm8350_data {struct wm8350* wm8350; } ;
struct wm8350 {int dummy; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int SND_SOC_CLOCK_OUT ; 
 int /*<<< orphan*/  WM8350_CLOCK_CONTROL_1 ; 
 int /*<<< orphan*/  WM8350_CLOCK_CONTROL_2 ; 
 int WM8350_FLL_CLK_SRC_MASK ; 
 int /*<<< orphan*/  WM8350_FLL_CONTROL_4 ; 
 int /*<<< orphan*/  WM8350_MCLK_DIR ; 
 int /*<<< orphan*/  WM8350_MCLK_SEL ; 
#define  WM8350_MCLK_SEL_MCLK 132 
#define  WM8350_MCLK_SEL_PLL_32K 131 
#define  WM8350_MCLK_SEL_PLL_ADC 130 
#define  WM8350_MCLK_SEL_PLL_DAC 129 
#define  WM8350_MCLK_SEL_PLL_MCLK 128 
 struct wm8350_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8350_clear_bits (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_set_bits (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8350_set_dai_sysclk(struct snd_soc_dai *codec_dai,
				 int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct wm8350_data *wm8350_data = snd_soc_component_get_drvdata(component);
	struct wm8350 *wm8350 = wm8350_data->wm8350;
	u16 fll_4;

	switch (clk_id) {
	case WM8350_MCLK_SEL_MCLK:
		wm8350_clear_bits(wm8350, WM8350_CLOCK_CONTROL_1,
				  WM8350_MCLK_SEL);
		break;
	case WM8350_MCLK_SEL_PLL_MCLK:
	case WM8350_MCLK_SEL_PLL_DAC:
	case WM8350_MCLK_SEL_PLL_ADC:
	case WM8350_MCLK_SEL_PLL_32K:
		wm8350_set_bits(wm8350, WM8350_CLOCK_CONTROL_1,
				WM8350_MCLK_SEL);
		fll_4 = snd_soc_component_read32(component, WM8350_FLL_CONTROL_4) &
		    ~WM8350_FLL_CLK_SRC_MASK;
		snd_soc_component_write(component, WM8350_FLL_CONTROL_4, fll_4 | clk_id);
		break;
	}

	/* MCLK direction */
	if (dir == SND_SOC_CLOCK_OUT)
		wm8350_set_bits(wm8350, WM8350_CLOCK_CONTROL_2,
				WM8350_MCLK_DIR);
	else
		wm8350_clear_bits(wm8350, WM8350_CLOCK_CONTROL_2,
				  WM8350_MCLK_DIR);

	return 0;
}