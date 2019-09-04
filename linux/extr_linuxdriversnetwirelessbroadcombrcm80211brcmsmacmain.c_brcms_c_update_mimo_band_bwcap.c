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
typedef  size_t uint ;
typedef  scalar_t__ u8 ;
struct brcms_c_info {struct brcms_band** bandstate; TYPE_1__* pub; } ;
struct brcms_band {scalar_t__ bandtype; int mimo_cap_40; } ;
struct TYPE_2__ {size_t _nbands; } ;

/* Variables and functions */
 scalar_t__ BRCMS_N_BW_20IN2G_40IN5G ; 
 scalar_t__ BRCMS_N_BW_40ALL ; 
 scalar_t__ BRCM_BAND_5G ; 

__attribute__((used)) static void brcms_c_update_mimo_band_bwcap(struct brcms_c_info *wlc, u8 bwcap)
{
	uint i;
	struct brcms_band *band;

	for (i = 0; i < wlc->pub->_nbands; i++) {
		band = wlc->bandstate[i];
		if (band->bandtype == BRCM_BAND_5G) {
			if ((bwcap == BRCMS_N_BW_40ALL)
			    || (bwcap == BRCMS_N_BW_20IN2G_40IN5G))
				band->mimo_cap_40 = true;
			else
				band->mimo_cap_40 = false;
		} else {
			if (bwcap == BRCMS_N_BW_40ALL)
				band->mimo_cap_40 = true;
			else
				band->mimo_cap_40 = false;
		}
	}
}