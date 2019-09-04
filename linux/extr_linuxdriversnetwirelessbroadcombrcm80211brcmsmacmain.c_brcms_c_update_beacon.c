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
struct brcms_c_info {int /*<<< orphan*/  beacon_dtim_period; int /*<<< orphan*/  beacon_tim_offset; int /*<<< orphan*/  beacon; int /*<<< orphan*/  defmacintmask; TYPE_1__* pub; struct brcms_bss_cfg* bsscfg; } ;
struct brcms_bss_cfg {scalar_t__ type; } ;
struct TYPE_2__ {scalar_t__ up; } ;

/* Variables and functions */
 scalar_t__ BRCMS_TYPE_ADHOC ; 
 scalar_t__ BRCMS_TYPE_AP ; 
 int /*<<< orphan*/  MI_BCNTPL ; 
 int /*<<< orphan*/  brcms_c_update_beacon_hw (struct brcms_c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void brcms_c_update_beacon(struct brcms_c_info *wlc)
{
	struct brcms_bss_cfg *bsscfg = wlc->bsscfg;

	if (wlc->pub->up && (bsscfg->type == BRCMS_TYPE_AP ||
			     bsscfg->type == BRCMS_TYPE_ADHOC)) {
		/* Clear the soft intmask */
		wlc->defmacintmask &= ~MI_BCNTPL;
		if (!wlc->beacon)
			return;
		brcms_c_update_beacon_hw(wlc, wlc->beacon,
					 wlc->beacon_tim_offset,
					 wlc->beacon_dtim_period);
	}
}