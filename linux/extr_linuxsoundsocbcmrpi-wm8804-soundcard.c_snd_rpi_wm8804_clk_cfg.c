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
struct wm8804_clk_cfg {unsigned int mclk_freq; int mclk_div; int sysclk_freq; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int WM8804_MCLKDIV_128FS ; 
 int WM8804_MCLKDIV_256FS ; 
 int /*<<< orphan*/  snd_clk44gpio ; 
 int /*<<< orphan*/  snd_clk48gpio ; 
 int snd_rpi_wm8804_enable_clock (unsigned int) ; 

__attribute__((used)) static void snd_rpi_wm8804_clk_cfg(unsigned int samplerate,
		struct wm8804_clk_cfg *clk_cfg)
{
	clk_cfg->mclk_freq = 0;
	clk_cfg->mclk_div = 1;
	clk_cfg->sysclk_freq = 27000000;

	if (samplerate <= 96000) {
		clk_cfg->mclk_freq = samplerate * 256;
		clk_cfg->mclk_div = WM8804_MCLKDIV_256FS;
	} else {
		clk_cfg->mclk_freq = samplerate * 128;
		clk_cfg->mclk_div = WM8804_MCLKDIV_128FS;
	}

	if (!(IS_ERR(snd_clk44gpio) || IS_ERR(snd_clk48gpio)))
		clk_cfg->sysclk_freq = snd_rpi_wm8804_enable_clock(samplerate);
}