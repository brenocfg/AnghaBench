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
struct TYPE_4__ {scalar_t__ READY; int /*<<< orphan*/  CONFIG; } ;
struct TYPE_3__ {int REGOUT0; } ;

/* Variables and functions */
 TYPE_2__* NRF_NVMC ; 
 TYPE_1__* NRF_UICR ; 
 int /*<<< orphan*/  NVIC_SystemReset () ; 
 int /*<<< orphan*/  NVMC_CONFIG_WEN_Ren ; 
 int /*<<< orphan*/  NVMC_CONFIG_WEN_Wen ; 
 scalar_t__ NVMC_READY_READY_Ready ; 
 int UICR_REGOUT0_VOUT_3V3 ; 
 int UICR_REGOUT0_VOUT_Msk ; 
 int UICR_REGOUT0_VOUT_Pos ; 
 scalar_t__ uicr_REGOUT0_erased () ; 

void board_modules_init0(void)
{
    if (uicr_REGOUT0_erased()) {

        // Wait for pending NVMC operations to finish.
        while (NRF_NVMC->READY != NVMC_READY_READY_Ready);

        // Enable write mode in NVMC.
        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
        while (NRF_NVMC->READY != NVMC_READY_READY_Ready);

        // Write 3v3 value to UICR->REGOUT0.
        NRF_UICR->REGOUT0 = (UICR_REGOUT0_VOUT_3V3 & UICR_REGOUT0_VOUT_Msk) << UICR_REGOUT0_VOUT_Pos;
        while (NRF_NVMC->READY != NVMC_READY_READY_Ready);

        // Enable read mode in NVMC.
        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
        while (NRF_NVMC->READY != NVMC_READY_READY_Ready);

        // Reset to apply the update.
        NVIC_SystemReset();
    }
}