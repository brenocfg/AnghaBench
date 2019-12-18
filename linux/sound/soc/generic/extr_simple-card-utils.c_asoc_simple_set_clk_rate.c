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
struct asoc_simple_dai {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int asoc_simple_set_clk_rate(struct asoc_simple_dai *simple_dai,
				    unsigned long rate)
{
	if (!simple_dai)
		return 0;

	if (!simple_dai->clk)
		return 0;

	if (clk_get_rate(simple_dai->clk) == rate)
		return 0;

	return clk_set_rate(simple_dai->clk, rate);
}