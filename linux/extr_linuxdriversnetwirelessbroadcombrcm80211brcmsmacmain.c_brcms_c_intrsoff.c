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
typedef  scalar_t__ u32 ;
struct brcms_hardware {int /*<<< orphan*/  d11core; int /*<<< orphan*/  clk; } ;
struct brcms_c_info {scalar_t__ macintstatus; scalar_t__ macintmask; struct brcms_hardware* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (scalar_t__) ; 
 int /*<<< orphan*/  bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

u32 brcms_c_intrsoff(struct brcms_c_info *wlc)
{
	struct brcms_hardware *wlc_hw = wlc->hw;
	u32 macintmask;

	if (!wlc_hw->clk)
		return 0;

	macintmask = wlc->macintmask;	/* isr can still happen */

	bcma_write32(wlc_hw->d11core, D11REGOFFS(macintmask), 0);
	(void)bcma_read32(wlc_hw->d11core, D11REGOFFS(macintmask));
	udelay(1);		/* ensure int line is no longer driven */
	wlc->macintmask = 0;

	/* return previous macintmask; resolve race between us and our isr */
	return wlc->macintstatus ? 0 : macintmask;
}