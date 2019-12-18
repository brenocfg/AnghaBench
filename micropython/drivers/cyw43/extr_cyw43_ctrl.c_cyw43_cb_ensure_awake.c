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
 int /*<<< orphan*/  CYW43_SLEEP_MAX ; 
 int /*<<< orphan*/  __HAL_RCC_SDMMC1_CLK_ENABLE () ; 
 scalar_t__ __HAL_RCC_SDMMC1_IS_CLK_DISABLED () ; 
 int /*<<< orphan*/  cyw43_sleep ; 
 int /*<<< orphan*/  sdio_enable_high_speed_4bit () ; 

void cyw43_cb_ensure_awake(void *cb_data) {
    cyw43_sleep = CYW43_SLEEP_MAX;
    #if !USE_SDIOIT
    if (__HAL_RCC_SDMMC1_IS_CLK_DISABLED()) {
        __HAL_RCC_SDMMC1_CLK_ENABLE(); // enable SDIO peripheral
        sdio_enable_high_speed_4bit();
    }
    #endif
}