#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  UART_BIT_RATE_115200 ; 
 int /*<<< orphan*/  mp_hal_rtc_init () ; 
 scalar_t__ uart_attached_to_dupterm ; 
 int /*<<< orphan*/  uart_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mp_hal_init(void) {
    //ets_wdt_disable(); // it's a pain while developing
    mp_hal_rtc_init();
    uart_init(UART_BIT_RATE_115200, UART_BIT_RATE_115200);
    uart_attached_to_dupterm = 0;
}