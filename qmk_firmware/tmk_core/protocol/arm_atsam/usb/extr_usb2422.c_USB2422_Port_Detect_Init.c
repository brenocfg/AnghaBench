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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBGC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_LED_OFF ; 
 int /*<<< orphan*/  DBG_LED_ON ; 
 int /*<<< orphan*/  DC_PORT_DETECT_INIT_BEGIN ; 
 int /*<<< orphan*/  DC_PORT_DETECT_INIT_COMPLETE ; 
 int /*<<< orphan*/  DC_PORT_DETECT_INIT_FAILED ; 
 int PORT_DETECT_RETRY_INTERVAL ; 
 int /*<<< orphan*/  USB_active () ; 
 int /*<<< orphan*/  USB_set_host_by_voltage () ; 
 int timer_read64 () ; 
 scalar_t__ v_con_1 ; 
 scalar_t__ v_con_2 ; 

uint8_t USB2422_Port_Detect_Init(void) {
    uint32_t port_detect_retry_ms;
    uint32_t tmod;

    DBGC(DC_PORT_DETECT_INIT_BEGIN);

    USB_set_host_by_voltage();

    port_detect_retry_ms = timer_read64() + PORT_DETECT_RETRY_INTERVAL;

    while (!USB_active()) {
        tmod = timer_read64() % PORT_DETECT_RETRY_INTERVAL;

        if (v_con_1 > v_con_2)  // Values updated from USB_set_host_by_voltage();
        {
            // 1 flash for port 1 detected
            if (tmod > 500 && tmod < 600) {
                DBG_LED_ON;
            } else {
                DBG_LED_OFF;
            }
        } else if (v_con_2 > v_con_1)  // Values updated from USB_set_host_by_voltage();
        {
            // 2 flash for port 2 detected
            if (tmod > 500 && tmod < 600) {
                DBG_LED_ON;
            } else if (tmod > 700 && tmod < 800) {
                DBG_LED_ON;
            } else {
                DBG_LED_OFF;
            }
        }

        if (timer_read64() > port_detect_retry_ms) {
            DBGC(DC_PORT_DETECT_INIT_FAILED);
            return 0;
        }
    }

    DBGC(DC_PORT_DETECT_INIT_COMPLETE);

    return 1;
}