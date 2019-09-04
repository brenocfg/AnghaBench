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
struct nuc900fb_info {unsigned long clk_rate; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long long) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 

__attribute__((used)) static unsigned int nuc900fb_calc_pixclk(struct nuc900fb_info *fbi,
					 unsigned long pixclk)
{
	unsigned long clk = fbi->clk_rate;
	unsigned long long div;

	/* pixclk is in picseconds. our clock is in Hz*/
	/* div = (clk * pixclk)/10^12 */
	div = (unsigned long long)clk * pixclk;
	div >>= 12;
	do_div(div, 625 * 625UL * 625);

	dev_dbg(fbi->dev, "pixclk %ld, divisor is %lld\n", pixclk, div);

	return div;
}