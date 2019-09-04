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
struct clk {int dummy; } ;
struct asoc_simple_dai {struct clk* clk; } ;

/* Variables and functions */

__attribute__((used)) static void asoc_simple_card_clk_register(struct asoc_simple_dai *dai,
					  struct clk *clk)
{
	dai->clk = clk;
}