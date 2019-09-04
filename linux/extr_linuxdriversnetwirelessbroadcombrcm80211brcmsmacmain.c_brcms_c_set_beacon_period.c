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
typedef  int u32 ;
typedef  int u16 ;
struct brcms_c_info {TYPE_2__* hw; TYPE_1__* default_bss; } ;
struct TYPE_4__ {int /*<<< orphan*/  d11core; } ;
struct TYPE_3__ {int beacon_period; } ;

/* Variables and functions */
 int CFPREP_CBI_SHIFT ; 
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  bcma_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcms_c_time_lock (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_time_unlock (struct brcms_c_info*) ; 
 int /*<<< orphan*/  tsf_cfprep ; 
 int /*<<< orphan*/  tsf_cfpstart ; 

int brcms_c_set_beacon_period(struct brcms_c_info *wlc, u16 period)
{
	u32 bcnint_us;

	if (period == 0)
		return -EINVAL;

	wlc->default_bss->beacon_period = period;

	bcnint_us = period << 10;
	brcms_c_time_lock(wlc);
	bcma_write32(wlc->hw->d11core, D11REGOFFS(tsf_cfprep),
		     (bcnint_us << CFPREP_CBI_SHIFT));
	bcma_write32(wlc->hw->d11core, D11REGOFFS(tsf_cfpstart), bcnint_us);
	brcms_c_time_unlock(wlc);

	return 0;
}