#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct brcms_c_info {int /*<<< orphan*/  asi; TYPE_3__* band; TYPE_2__* pub; TYPE_1__* hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  bandunit; } ;
struct TYPE_5__ {int /*<<< orphan*/  unit; } ;
struct TYPE_4__ {int /*<<< orphan*/  d11core; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_c_antsel_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_set_ratetable (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_ucode_mac_upd (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_dbg_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_c_bsinit(struct brcms_c_info *wlc)
{
	brcms_dbg_info(wlc->hw->d11core, "wl%d: bandunit %d\n",
		       wlc->pub->unit, wlc->band->bandunit);

	/* write ucode ACK/CTS rate table */
	brcms_c_set_ratetable(wlc);

	/* update some band specific mac configuration */
	brcms_c_ucode_mac_upd(wlc);

	/* init antenna selection */
	brcms_c_antsel_init(wlc->asi);

}