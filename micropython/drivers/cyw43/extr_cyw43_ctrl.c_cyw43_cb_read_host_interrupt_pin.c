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
 int mp_hal_pin_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pyb_pin_WL_HOST_WAKE ; 
 int /*<<< orphan*/  pyb_pin_WL_SDIO_1 ; 

int cyw43_cb_read_host_interrupt_pin(void *cb_data) {
    #ifdef pyb_pin_WL_HOST_WAKE
    return mp_hal_pin_read(pyb_pin_WL_HOST_WAKE);
    #else
    return mp_hal_pin_read(pyb_pin_WL_SDIO_1);
    #endif
}