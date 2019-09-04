#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct brcms_hardware {int up; TYPE_2__* wlc; TYPE_1__* band; } ;
struct TYPE_4__ {int /*<<< orphan*/  wl; } ;
struct TYPE_3__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CLKMODE_DYNAMIC ; 
 int /*<<< orphan*/  brcms_b_clkctl_clk (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_intrson (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_hw_state_upd (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int brcms_b_up_finish(struct brcms_hardware *wlc_hw)
{
	wlc_hw->up = true;
	wlc_phy_hw_state_upd(wlc_hw->band->pi, true);

	/* FULLY enable dynamic power control and d11 core interrupt */
	brcms_b_clkctl_clk(wlc_hw, BCMA_CLKMODE_DYNAMIC);
	brcms_intrson(wlc_hw->wlc->wl);
	return 0;
}