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
struct TYPE_4__ {TYPE_1__* GPIOPORT; } ;
struct TYPE_3__ {scalar_t__ PERM; } ;

/* Variables and functions */
 int /*<<< orphan*/  NRF_CLOCK_S ; 
 int /*<<< orphan*/  NRF_DPPIC_S ; 
 int /*<<< orphan*/  NRF_EGU1_S ; 
 int /*<<< orphan*/  NRF_EGU2_S ; 
 int /*<<< orphan*/  NRF_EGU3_S ; 
 int /*<<< orphan*/  NRF_EGU4_S ; 
 int /*<<< orphan*/  NRF_EGU5_S ; 
 int /*<<< orphan*/  NRF_FPU_S ; 
 int /*<<< orphan*/  NRF_GPIOTE1_NS ; 
 int /*<<< orphan*/  NRF_I2S_S ; 
 int /*<<< orphan*/  NRF_IPC_S ; 
 int /*<<< orphan*/  NRF_NVMC_S ; 
 int /*<<< orphan*/  NRF_P0_NS ; 
 int /*<<< orphan*/  NRF_PDM_S ; 
 int /*<<< orphan*/  NRF_PWM0_S ; 
 int /*<<< orphan*/  NRF_PWM1_S ; 
 int /*<<< orphan*/  NRF_PWM2_S ; 
 int /*<<< orphan*/  NRF_PWM3_S ; 
 int /*<<< orphan*/  NRF_REGULATORS_S ; 
 int /*<<< orphan*/  NRF_RTC0_S ; 
 int /*<<< orphan*/  NRF_RTC1_S ; 
 int /*<<< orphan*/  NRF_SAADC_S ; 
 TYPE_2__* NRF_SPU_S ; 
 int /*<<< orphan*/  NRF_TIMER0_S ; 
 int /*<<< orphan*/  NRF_TIMER1_S ; 
 int /*<<< orphan*/  NRF_TIMER2_S ; 
 int /*<<< orphan*/  NRF_UARTE0_S ; 
 int /*<<< orphan*/  NRF_UARTE1_S ; 
 int /*<<< orphan*/  NRF_UARTE2_S ; 
 int /*<<< orphan*/  NRF_UARTE3_S ; 
 int /*<<< orphan*/  NRF_VMC_S ; 
 int /*<<< orphan*/  NRF_WDT_S ; 
 int /*<<< orphan*/  PERIPHERAL_ID_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peripheral_setup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void configure_peripherals(void)
{
    NRF_SPU_S->GPIOPORT[0].PERM = 0;
    peripheral_setup(PERIPHERAL_ID_GET(NRF_REGULATORS_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_CLOCK_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_UARTE0_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_UARTE1_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_UARTE2_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_UARTE3_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_SAADC_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_TIMER0_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_TIMER1_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_TIMER2_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_RTC0_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_RTC1_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_DPPIC_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_WDT_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_EGU1_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_EGU2_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_EGU3_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_EGU4_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_EGU5_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_PWM0_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_PWM1_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_PWM2_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_PWM3_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_PDM_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_I2S_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_IPC_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_FPU_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_GPIOTE1_NS));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_NVMC_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_VMC_S));
    peripheral_setup(PERIPHERAL_ID_GET(NRF_P0_NS));
}