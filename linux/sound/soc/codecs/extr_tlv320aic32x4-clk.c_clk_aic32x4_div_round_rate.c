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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long DIV_ROUND_UP (unsigned long,unsigned long) ; 
 long EINVAL ; 

__attribute__((used)) static long clk_aic32x4_div_round_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long *parent_rate)
{
	unsigned long divisor;

	divisor = DIV_ROUND_UP(*parent_rate, rate);
	if (divisor > 128)
		return -EINVAL;

	return DIV_ROUND_UP(*parent_rate, divisor);
}