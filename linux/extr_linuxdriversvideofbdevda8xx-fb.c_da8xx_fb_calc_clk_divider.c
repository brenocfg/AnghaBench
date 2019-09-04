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
struct da8xx_fb_par {unsigned int lcdc_clk_rate; int /*<<< orphan*/  lcdc_clk; } ;

/* Variables and functions */
 unsigned int CLK_MAX_DIV ; 
 unsigned int CLK_MIN_DIV ; 
 int PICOS2KHZ (unsigned int) ; 
 unsigned int clk_round_rate (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int da8xx_fb_calc_clk_divider(struct da8xx_fb_par *par,
					      unsigned pixclock,
					      unsigned *lcdc_clk_rate)
{
	unsigned lcdc_clk_div;

	pixclock = PICOS2KHZ(pixclock) * 1000;

	*lcdc_clk_rate = par->lcdc_clk_rate;

	if (pixclock < (*lcdc_clk_rate / CLK_MAX_DIV)) {
		*lcdc_clk_rate = clk_round_rate(par->lcdc_clk,
						pixclock * CLK_MAX_DIV);
		lcdc_clk_div = CLK_MAX_DIV;
	} else if (pixclock > (*lcdc_clk_rate / CLK_MIN_DIV)) {
		*lcdc_clk_rate = clk_round_rate(par->lcdc_clk,
						pixclock * CLK_MIN_DIV);
		lcdc_clk_div = CLK_MIN_DIV;
	} else {
		lcdc_clk_div = *lcdc_clk_rate / pixclock;
	}

	return lcdc_clk_div;
}