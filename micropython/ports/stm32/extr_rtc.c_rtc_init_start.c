#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {int BDCR; int CSR; } ;
struct TYPE_5__ {int /*<<< orphan*/  OutPutType; int /*<<< orphan*/  OutPutPolarity; int /*<<< orphan*/  OutPut; int /*<<< orphan*/  SynchPrediv; int /*<<< orphan*/  AsynchPrediv; int /*<<< orphan*/  HourFormat; } ;
struct TYPE_6__ {TYPE_1__ Init; int /*<<< orphan*/  Instance; } ;

/* Variables and functions */
 int HAL_GetTick () ; 
 int /*<<< orphan*/  HAL_PWR_EnableBkUpAccess () ; 
 int /*<<< orphan*/  MICROPY_HW_RTC_USE_BYPASS ; 
 int /*<<< orphan*/  PYB_RTC_MspInit_Kick (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* RCC ; 
 int RCC_BDCR_LSEON ; 
 int RCC_BDCR_LSERDY ; 
 int RCC_BDCR_RTCEN ; 
 int RCC_BDCR_RTCSEL ; 
 int RCC_BDCR_RTCSEL_0 ; 
 int RCC_BDCR_RTCSEL_1 ; 
 int RCC_CSR_LSION ; 
 int /*<<< orphan*/  RTC ; 
 TYPE_2__ RTCHandle ; 
 int /*<<< orphan*/  RTC_ASYNCH_PREDIV ; 
 int /*<<< orphan*/  RTC_HOURFORMAT_24 ; 
 int /*<<< orphan*/  RTC_OUTPUT_DISABLE ; 
 int /*<<< orphan*/  RTC_OUTPUT_POLARITY_HIGH ; 
 int /*<<< orphan*/  RTC_OUTPUT_TYPE_OPENDRAIN ; 
 int /*<<< orphan*/  RTC_SYNCH_PREDIV ; 
 int /*<<< orphan*/  __HAL_RCC_CLEAR_RESET_FLAGS () ; 
 int rtc_info ; 
 int rtc_need_init_finalise ; 
 int rtc_startup_tick ; 
 int /*<<< orphan*/  rtc_use_lse ; 

void rtc_init_start(bool force_init) {
    RTCHandle.Instance = RTC;

    /* Configure RTC prescaler and RTC data registers */
    /* RTC configured as follow:
      - Hour Format    = Format 24
      - Asynch Prediv  = Value according to source clock
      - Synch Prediv   = Value according to source clock
      - OutPut         = Output Disable
      - OutPutPolarity = High Polarity
      - OutPutType     = Open Drain */
    RTCHandle.Init.HourFormat = RTC_HOURFORMAT_24;
    RTCHandle.Init.AsynchPrediv = RTC_ASYNCH_PREDIV;
    RTCHandle.Init.SynchPrediv = RTC_SYNCH_PREDIV;
    RTCHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
    RTCHandle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    RTCHandle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;

    rtc_need_init_finalise = false;

    if (!force_init) {
        uint32_t bdcr = RCC->BDCR;
        if ((bdcr & (RCC_BDCR_RTCEN | RCC_BDCR_RTCSEL | RCC_BDCR_LSEON | RCC_BDCR_LSERDY))
            == (RCC_BDCR_RTCEN | RCC_BDCR_RTCSEL_0 | RCC_BDCR_LSEON | RCC_BDCR_LSERDY)) {
            // LSE is enabled & ready --> no need to (re-)init RTC
            // remove Backup Domain write protection
            HAL_PWR_EnableBkUpAccess();
            // Clear source Reset Flag
            __HAL_RCC_CLEAR_RESET_FLAGS();
            // provide some status information
            rtc_info |= 0x40000 | (RCC->BDCR & 7) | (RCC->CSR & 3) << 8;
            return;
        } else if ((bdcr & (RCC_BDCR_RTCEN | RCC_BDCR_RTCSEL))
            == (RCC_BDCR_RTCEN | RCC_BDCR_RTCSEL_1)) {
            // LSI configured as the RTC clock source --> no need to (re-)init RTC
            // remove Backup Domain write protection
            HAL_PWR_EnableBkUpAccess();
            // Clear source Reset Flag
            __HAL_RCC_CLEAR_RESET_FLAGS();
            // Turn the LSI on (it may need this even if the RTC is running)
            RCC->CSR |= RCC_CSR_LSION;
            // provide some status information
            rtc_info |= 0x80000 | (RCC->BDCR & 7) | (RCC->CSR & 3) << 8;
            return;
        }
    }

    rtc_startup_tick = HAL_GetTick();
    rtc_info = 0x3f000000 | (rtc_startup_tick & 0xffffff);
    PYB_RTC_MspInit_Kick(&RTCHandle, rtc_use_lse, MICROPY_HW_RTC_USE_BYPASS);
}