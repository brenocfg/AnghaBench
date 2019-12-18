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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int PLLSAICFGR; int CR; int /*<<< orphan*/  DCKCFGR2; } ;
struct TYPE_5__ {int /*<<< orphan*/  SYSCLKSource; } ;
typedef  TYPE_1__ RCC_ClkInitTypeDef ;

/* Variables and functions */
 int FLASH_LATENCY_0 ; 
 int FLASH_LATENCY_1 ; 
 int FLASH_LATENCY_2 ; 
 int FLASH_LATENCY_3 ; 
 int FLASH_LATENCY_4 ; 
 int FLASH_LATENCY_5 ; 
 int FLASH_LATENCY_6 ; 
 int FLASH_LATENCY_7 ; 
 scalar_t__ HAL_OK ; 
 scalar_t__ HAL_PWREx_ControlVoltageScaling (int) ; 
 scalar_t__ HAL_RCC_ClockConfig (TYPE_1__*,int) ; 
 int MICROPY_HW_FLASH_LATENCY ; 
 int MP_EIO ; 
 int MP_ETIMEDOUT ; 
 int PWR_REGULATOR_VOLTAGE_SCALE1 ; 
 int PWR_REGULATOR_VOLTAGE_SCALE2 ; 
 int PWR_REGULATOR_VOLTAGE_SCALE3 ; 
 TYPE_3__* RCC ; 
 int RCC_CR_PLLSAION ; 
 int RCC_CR_PLLSAIRDY ; 
 int /*<<< orphan*/  RCC_DCKCFGR2_CK48MSEL ; 
 int const RCC_PLLSAICFGR_PLLSAIN_Pos ; 
 int const RCC_PLLSAICFGR_PLLSAIP_Pos ; 
 int const RCC_PLLSAICFGR_PLLSAIQ_Pos ; 
 int /*<<< orphan*/  RCC_SYSCLKSOURCE_PLLCLK ; 
 int mp_hal_ticks_ms () ; 

int powerctrl_rcc_clock_config_pll(RCC_ClkInitTypeDef *rcc_init, uint32_t sysclk_mhz, bool need_pllsai) {
    uint32_t flash_latency;

    #if defined(STM32F7)

    if (need_pllsai) {
        // Configure PLLSAI at 48MHz for those peripherals that need this freq
        const uint32_t pllsain = 192;
        const uint32_t pllsaip = 4;
        const uint32_t pllsaiq = 2;
        RCC->PLLSAICFGR = pllsaiq << RCC_PLLSAICFGR_PLLSAIQ_Pos
            | (pllsaip / 2 - 1) << RCC_PLLSAICFGR_PLLSAIP_Pos
            | pllsain << RCC_PLLSAICFGR_PLLSAIN_Pos;
        RCC->CR |= RCC_CR_PLLSAION;
        uint32_t ticks = mp_hal_ticks_ms();
        while (!(RCC->CR & RCC_CR_PLLSAIRDY)) {
            if (mp_hal_ticks_ms() - ticks > 200) {
                return -MP_ETIMEDOUT;
            }
        }
        RCC->DCKCFGR2 |= RCC_DCKCFGR2_CK48MSEL;
    }

    // If possible, scale down the internal voltage regulator to save power
    uint32_t volt_scale;
    if (sysclk_mhz <= 151) {
        volt_scale = PWR_REGULATOR_VOLTAGE_SCALE3;
    } else if (sysclk_mhz <= 180) {
        volt_scale = PWR_REGULATOR_VOLTAGE_SCALE2;
    } else {
        volt_scale = PWR_REGULATOR_VOLTAGE_SCALE1;
    }
    if (HAL_PWREx_ControlVoltageScaling(volt_scale) != HAL_OK) {
        return -MP_EIO;
    }

    // These flash_latency values assume a supply voltage between 2.7V and 3.6V
    if (sysclk_mhz <= 30) {
        flash_latency = FLASH_LATENCY_0;
    } else if (sysclk_mhz <= 60) {
        flash_latency = FLASH_LATENCY_1;
    } else if (sysclk_mhz <= 90) {
        flash_latency = FLASH_LATENCY_2;
    } else if (sysclk_mhz <= 120) {
        flash_latency = FLASH_LATENCY_3;
    } else if (sysclk_mhz <= 150) {
        flash_latency = FLASH_LATENCY_4;
    } else if (sysclk_mhz <= 180) {
        flash_latency = FLASH_LATENCY_5;
    } else if (sysclk_mhz <= 210) {
        flash_latency = FLASH_LATENCY_6;
    } else {
        flash_latency = FLASH_LATENCY_7;
    }

    #elif defined(MICROPY_HW_FLASH_LATENCY)
    flash_latency = MICROPY_HW_FLASH_LATENCY;
    #else
    flash_latency = FLASH_LATENCY_5;
    #endif

    rcc_init->SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    if (HAL_RCC_ClockConfig(rcc_init, flash_latency) != HAL_OK) {
        return -MP_EIO;
    }

    return 0;
}