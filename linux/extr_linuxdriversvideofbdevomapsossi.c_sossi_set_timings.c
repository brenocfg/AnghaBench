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
struct extif_timings {int /*<<< orphan*/ * tim; int /*<<< orphan*/  converted; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk_div; int /*<<< orphan*/ * clk_tw1; int /*<<< orphan*/ * clk_tw0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t RD_ACCESS ; 
 size_t WR_ACCESS ; 
 TYPE_1__ sossi ; 

__attribute__((used)) static void sossi_set_timings(const struct extif_timings *t)
{
	BUG_ON(!t->converted);

	sossi.clk_tw0[RD_ACCESS] = t->tim[0];
	sossi.clk_tw1[RD_ACCESS] = t->tim[1];

	sossi.clk_tw0[WR_ACCESS] = t->tim[2];
	sossi.clk_tw1[WR_ACCESS] = t->tim[3];

	sossi.clk_div = t->tim[4];
}