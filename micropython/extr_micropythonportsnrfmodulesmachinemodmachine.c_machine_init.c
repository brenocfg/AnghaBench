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
typedef  int uint32_t ;
struct TYPE_2__ {int RESETREAS; } ;

/* Variables and functions */
 TYPE_1__* NRF_POWER ; 
 int POWER_RESETREAS_DIF_Msk ; 
 int POWER_RESETREAS_DOG_Msk ; 
 int POWER_RESETREAS_LOCKUP_Msk ; 
 int POWER_RESETREAS_LPCOMP_Msk ; 
 int POWER_RESETREAS_OFF_Msk ; 
 int POWER_RESETREAS_RESETPIN_Msk ; 
 int POWER_RESETREAS_SREQ_Msk ; 
 int PYB_RESET_DIF ; 
 int PYB_RESET_HARD ; 
 int PYB_RESET_LOCKUP ; 
 int PYB_RESET_LPCOMP ; 
 int PYB_RESET_POWER_ON ; 
 int PYB_RESET_SOFT ; 
 int PYB_RESET_WDT ; 
 int reset_cause ; 

void machine_init(void) {
    uint32_t state = NRF_POWER->RESETREAS;
    if (state & POWER_RESETREAS_RESETPIN_Msk) {
        reset_cause = PYB_RESET_HARD;
    } else if (state & POWER_RESETREAS_DOG_Msk) {
        reset_cause = PYB_RESET_WDT;
    } else if (state & POWER_RESETREAS_SREQ_Msk) {
        reset_cause = PYB_RESET_SOFT;
    } else if (state & POWER_RESETREAS_LOCKUP_Msk) {
        reset_cause = PYB_RESET_LOCKUP;
    } else if (state & POWER_RESETREAS_OFF_Msk) {
        reset_cause = PYB_RESET_POWER_ON;
    } else if (state & POWER_RESETREAS_LPCOMP_Msk) {
        reset_cause = PYB_RESET_LPCOMP;
    } else if (state & POWER_RESETREAS_DIF_Msk) {
        reset_cause = PYB_RESET_DIF;
#if defined(NRF52_SERIES)
    } else if (state & POWER_RESETREAS_NFC_Msk) {
        reset_cause = PYB_RESET_NFC;
#endif
    }

    // clear reset reason
    NRF_POWER->RESETREAS = (1 << reset_cause);
}