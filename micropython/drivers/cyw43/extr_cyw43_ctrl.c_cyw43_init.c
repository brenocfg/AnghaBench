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
struct TYPE_4__ {int pend_disassoc; int pend_rejoin; int pend_rejoin_wpa; int ap_channel; scalar_t__ ap_key_len; scalar_t__ ap_ssid_len; scalar_t__ wifi_join_state; scalar_t__ wifi_scan_state; scalar_t__ itf_state; int /*<<< orphan*/  cyw43_ll; } ;
typedef  TYPE_1__ cyw43_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_HAL_PIN_MODE_INPUT ; 
 int /*<<< orphan*/  MP_HAL_PIN_MODE_OUTPUT ; 
 int /*<<< orphan*/  MP_HAL_PIN_PULL_NONE ; 
 int /*<<< orphan*/  cyw43_ll_init (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * cyw43_poll ; 
 int /*<<< orphan*/  mp_hal_pin_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_hal_pin_low (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pyb_pin_WL_HOST_WAKE ; 
 int /*<<< orphan*/  pyb_pin_WL_REG_ON ; 
 int /*<<< orphan*/  pyb_pin_WL_RFSW_VDD ; 

void cyw43_init(cyw43_t *self) {
    #ifdef pyb_pin_WL_HOST_WAKE
    mp_hal_pin_config(pyb_pin_WL_HOST_WAKE, MP_HAL_PIN_MODE_INPUT, MP_HAL_PIN_PULL_NONE, 0);
    #endif
    mp_hal_pin_config(pyb_pin_WL_REG_ON, MP_HAL_PIN_MODE_OUTPUT, MP_HAL_PIN_PULL_NONE, 0);
    mp_hal_pin_low(pyb_pin_WL_REG_ON);
    #ifdef pyb_pin_WL_RFSW_VDD
    mp_hal_pin_config(pyb_pin_WL_RFSW_VDD, MP_HAL_PIN_MODE_OUTPUT, MP_HAL_PIN_PULL_NONE, 0); // RF-switch power
    mp_hal_pin_low(pyb_pin_WL_RFSW_VDD);
    #endif

    cyw43_ll_init(&self->cyw43_ll, self);

    self->itf_state = 0;
    self->wifi_scan_state = 0;
    self->wifi_join_state = 0;
    self->pend_disassoc = false;
    self->pend_rejoin= false;
    self->pend_rejoin_wpa = false;
    self->ap_channel = 3;
    self->ap_ssid_len = 0;
    self->ap_key_len = 0;

    cyw43_poll = NULL;
}