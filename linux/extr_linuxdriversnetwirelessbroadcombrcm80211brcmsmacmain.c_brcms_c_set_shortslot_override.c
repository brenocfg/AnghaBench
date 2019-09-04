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
struct brcms_c_info {scalar_t__ shortslot_override; int shortslot; TYPE_2__* pub; TYPE_1__* band; } ;
typedef  scalar_t__ s8 ;
struct TYPE_4__ {scalar_t__ up; scalar_t__ associated; } ;
struct TYPE_3__ {scalar_t__ bandtype; } ;

/* Variables and functions */
 scalar_t__ BRCMS_SHORTSLOT_AUTO ; 
 scalar_t__ BRCMS_SHORTSLOT_ON ; 
 scalar_t__ BRCM_BAND_5G ; 
 int /*<<< orphan*/  brcms_c_switch_shortslot (struct brcms_c_info*,int) ; 

void brcms_c_set_shortslot_override(struct brcms_c_info *wlc, s8 sslot_override)
{
	wlc->shortslot_override = sslot_override;

	/*
	 * shortslot is an 11g feature, so no more work if we are
	 * currently on the 5G band
	 */
	if (wlc->band->bandtype == BRCM_BAND_5G)
		return;

	if (wlc->pub->up && wlc->pub->associated) {
		/* let watchdog or beacon processing update shortslot */
	} else if (wlc->pub->up) {
		/* unassociated shortslot is off */
		brcms_c_switch_shortslot(wlc, false);
	} else {
		/* driver is down, so just update the brcms_c_info
		 * value */
		if (wlc->shortslot_override == BRCMS_SHORTSLOT_AUTO)
			wlc->shortslot = false;
		else
			wlc->shortslot =
			    (wlc->shortslot_override ==
			     BRCMS_SHORTSLOT_ON);
	}
}