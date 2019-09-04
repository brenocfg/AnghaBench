#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ has_clksel; } ;
struct s3c_fb {int /*<<< orphan*/  dev; int /*<<< orphan*/  lcd_clk; int /*<<< orphan*/  bus_clk; TYPE_1__ variant; } ;

/* Variables and functions */
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned long,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long) ; 

__attribute__((used)) static int s3c_fb_calc_pixclk(struct s3c_fb *sfb, unsigned int pixclk)
{
	unsigned long clk;
	unsigned long long tmp;
	unsigned int result;

	if (sfb->variant.has_clksel)
		clk = clk_get_rate(sfb->bus_clk);
	else
		clk = clk_get_rate(sfb->lcd_clk);

	tmp = (unsigned long long)clk;
	tmp *= pixclk;

	do_div(tmp, 1000000000UL);
	result = (unsigned int)tmp / 1000;

	dev_dbg(sfb->dev, "pixclk=%u, clk=%lu, div=%d (%lu)\n",
		pixclk, clk, result, result ? clk / result : clk);

	return result;
}