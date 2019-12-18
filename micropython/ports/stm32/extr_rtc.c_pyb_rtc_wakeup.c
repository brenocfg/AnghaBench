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
typedef  scalar_t__ mp_obj_t ;
typedef  int mp_int_t ;
struct TYPE_6__ {int IMR1; int RTSR1; int IMR; int RTSR; int PR1; int PR; } ;
struct TYPE_5__ {int IMR1; int PR1; } ;
struct TYPE_4__ {int WPR; int CR; int ISR; int WUTR; } ;

/* Variables and functions */
 TYPE_3__* EXTI ; 
 TYPE_2__* EXTI_D1 ; 
 size_t EXTI_RTC_WAKEUP ; 
 int /*<<< orphan*/  HAL_NVIC_DisableIRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAL_NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_PRI_RTC_WKUP ; 
 scalar_t__* MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVIC_SetPriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* RTC ; 
 int RTC_CR_WUTE ; 
 int RTC_CR_WUTIE ; 
 int RTC_ISR_WUTF ; 
 int RTC_ISR_WUTWF ; 
 int /*<<< orphan*/  RTC_WKUP_IRQn ; 
 scalar_t__ const mp_const_none ; 
 int mp_obj_get_int (scalar_t__ const) ; 
 int /*<<< orphan*/  mp_raise_ValueError (char*) ; 
 int /*<<< orphan*/  pyb_extint_callback ; 
 int /*<<< orphan*/  rtc_init_finalise () ; 

mp_obj_t pyb_rtc_wakeup(size_t n_args, const mp_obj_t *args) {
    // wut is wakeup counter start value, wucksel is clock source
    // counter is decremented at wucksel rate, and wakes the MCU when it gets to 0
    // wucksel=0b000 is RTC/16 (RTC runs at 32768Hz)
    // wucksel=0b001 is RTC/8
    // wucksel=0b010 is RTC/4
    // wucksel=0b011 is RTC/2
    // wucksel=0b100 is 1Hz clock
    // wucksel=0b110 is 1Hz clock with 0x10000 added to wut
    // so a 1 second wakeup could be wut=2047, wucksel=0b000, or wut=4095, wucksel=0b001, etc

    rtc_init_finalise();

    // disable wakeup IRQ while we configure it
    HAL_NVIC_DisableIRQ(RTC_WKUP_IRQn);

    bool enable = false;
    mp_int_t wucksel;
    mp_int_t wut;
    mp_obj_t callback = mp_const_none;
    if (n_args <= 3) {
        if (args[1] == mp_const_none) {
            // disable wakeup
        } else {
            // time given in ms
            mp_int_t ms = mp_obj_get_int(args[1]);
            mp_int_t div = 2;
            wucksel = 3;
            while (div <= 16 && ms > 2000 * div) {
                div *= 2;
                wucksel -= 1;
            }
            if (div <= 16) {
                wut = 32768 / div * ms / 1000;
            } else {
                // use 1Hz clock
                wucksel = 4;
                wut = ms / 1000;
                if (wut > 0x10000) {
                    // wut too large for 16-bit register, try to offset by 0x10000
                    wucksel = 6;
                    wut -= 0x10000;
                    if (wut > 0x10000) {
                        // wut still too large
                        mp_raise_ValueError("wakeup value too large");
                    }
                }
            }
            // wut register should be 1 less than desired value, but guard against wut=0
            if (wut > 0) {
                wut -= 1;
            }
            enable = true;
        }
        if (n_args == 3) {
            callback = args[2];
        }
    } else {
        // config values given directly
        wucksel = mp_obj_get_int(args[1]);
        wut = mp_obj_get_int(args[2]);
        callback = args[3];
        enable = true;
    }

    // set the callback
    MP_STATE_PORT(pyb_extint_callback)[EXTI_RTC_WAKEUP] = callback;

    // disable register write protection
    RTC->WPR = 0xca;
    RTC->WPR = 0x53;

    // clear WUTE
    RTC->CR &= ~RTC_CR_WUTE;

    // wait until WUTWF is set
    while (!(RTC->ISR & RTC_ISR_WUTWF)) {
    }

    if (enable) {
        // program WUT
        RTC->WUTR = wut;

        // set WUTIE to enable wakeup interrupts
        // set WUTE to enable wakeup
        // program WUCKSEL
        RTC->CR = (RTC->CR & ~7) | (1 << 14) | (1 << 10) | (wucksel & 7);

        // enable register write protection
        RTC->WPR = 0xff;

        // enable external interrupts on line EXTI_RTC_WAKEUP
        #if defined(STM32L4) || defined(STM32WB)
        EXTI->IMR1 |= 1 << EXTI_RTC_WAKEUP;
        EXTI->RTSR1 |= 1 << EXTI_RTC_WAKEUP;
        #elif defined(STM32H7)
        EXTI_D1->IMR1 |= 1 << EXTI_RTC_WAKEUP;
        EXTI->RTSR1 |= 1 << EXTI_RTC_WAKEUP;
        #else
        EXTI->IMR |= 1 << EXTI_RTC_WAKEUP;
        EXTI->RTSR |= 1 << EXTI_RTC_WAKEUP;
        #endif

        // clear interrupt flags
        RTC->ISR &= ~RTC_ISR_WUTF;
        #if defined(STM32L4) || defined(STM32WB)
        EXTI->PR1 = 1 << EXTI_RTC_WAKEUP;
        #elif defined(STM32H7)
        EXTI_D1->PR1 = 1 << EXTI_RTC_WAKEUP;
        #else
        EXTI->PR = 1 << EXTI_RTC_WAKEUP;
        #endif

        NVIC_SetPriority(RTC_WKUP_IRQn, IRQ_PRI_RTC_WKUP);
        HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);

        //printf("wut=%d wucksel=%d\n", wut, wucksel);
    } else {
        // clear WUTIE to disable interrupts
        RTC->CR &= ~RTC_CR_WUTIE;

        // enable register write protection
        RTC->WPR = 0xff;

        // disable external interrupts on line EXTI_RTC_WAKEUP
        #if defined(STM32L4) || defined(STM32WB)
        EXTI->IMR1 &= ~(1 << EXTI_RTC_WAKEUP);
        #elif defined(STM32H7)
        EXTI_D1->IMR1 |= 1 << EXTI_RTC_WAKEUP;
        #else
        EXTI->IMR &= ~(1 << EXTI_RTC_WAKEUP);
        #endif
    }

    return mp_const_none;
}