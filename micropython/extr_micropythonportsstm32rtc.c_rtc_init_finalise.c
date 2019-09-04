#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  State; } ;

/* Variables and functions */
 int HAL_GetTick () ; 
 scalar_t__ HAL_OK ; 
 int /*<<< orphan*/  HAL_PWR_EnableBkUpAccess () ; 
 int /*<<< orphan*/  HAL_RTC_STATE_RESET ; 
 scalar_t__ PYB_RTC_Init (TYPE_1__*) ; 
 int /*<<< orphan*/  PYB_RTC_MspInit_Kick (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  RCC_FLAG_PINRST ; 
 int /*<<< orphan*/  RCC_FLAG_PORRST ; 
 scalar_t__ RESET ; 
 TYPE_1__ RTCHandle ; 
 int /*<<< orphan*/  RTC_CalendarConfig () ; 
 int /*<<< orphan*/  __HAL_RCC_CLEAR_RESET_FLAGS () ; 
 scalar_t__ __HAL_RCC_GET_FLAG (int /*<<< orphan*/ ) ; 
 int rtc_info ; 
 int rtc_need_init_finalise ; 
 int rtc_startup_tick ; 
 int rtc_use_lse ; 

void rtc_init_finalise() {
    if (!rtc_need_init_finalise) {
        return;
    }

    rtc_info = 0;
    while (PYB_RTC_Init(&RTCHandle) != HAL_OK) {
        if (rtc_use_lse) {
            #if MICROPY_HW_RTC_USE_BYPASS
            if (RCC->BDCR & RCC_BDCR_LSEBYP) {
                // LSEBYP failed, fallback to LSE non-bypass
                rtc_info |= 0x02000000;
            } else
            #endif
            {
                // LSE failed, fallback to LSI
                rtc_use_lse = false;
                rtc_info |= 0x01000000;
            }
            rtc_startup_tick = HAL_GetTick();
            PYB_RTC_MspInit_Kick(&RTCHandle, rtc_use_lse, false);
            HAL_PWR_EnableBkUpAccess();
            RTCHandle.State = HAL_RTC_STATE_RESET;
        } else {
            // init error
            rtc_info |= 0xffff; // indicate error
            return;
        }
    }

    // RTC started successfully
    rtc_info = 0x20000000;

    // record if LSE or LSI is used
    rtc_info |= (rtc_use_lse << 28);

    // record how long it took for the RTC to start up
    rtc_info |= (HAL_GetTick() - rtc_startup_tick) & 0xffff;

    // fresh reset; configure RTC Calendar
    RTC_CalendarConfig();
    #if defined(STM32L4)
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST) != RESET) {
    #else
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST) != RESET) {
    #endif
        // power on reset occurred
        rtc_info |= 0x10000;
    }
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST) != RESET) {
        // external reset occurred
        rtc_info |= 0x20000;
    }
    // Clear source Reset Flag
    __HAL_RCC_CLEAR_RESET_FLAGS();
    rtc_need_init_finalise = false;
}