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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADC0_init () ; 
 int /*<<< orphan*/  ADC_5V ; 
 int /*<<< orphan*/  CDC_init () ; 
 int /*<<< orphan*/  CLK_init () ; 
 int /*<<< orphan*/  DBGC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_1_ENA ; 
 int /*<<< orphan*/  DBG_1_OFF ; 
 int /*<<< orphan*/  DBG_2_ENA ; 
 int /*<<< orphan*/  DBG_2_OFF ; 
 int /*<<< orphan*/  DBG_3_ENA ; 
 int /*<<< orphan*/  DBG_3_OFF ; 
 int /*<<< orphan*/  DBG_LED_ENA ; 
 int /*<<< orphan*/  DBG_LED_OFF ; 
 int /*<<< orphan*/  DC_MAIN_CDC_INIT_BEGIN ; 
 int /*<<< orphan*/  DC_MAIN_CDC_INIT_COMPLETE ; 
 int /*<<< orphan*/  DC_MAIN_UDC_START_BEGIN ; 
 int /*<<< orphan*/  DC_MAIN_UDC_START_COMPLETE ; 
 int I2C3733_Init_Control () ; 
 int I2C3733_Init_Drivers () ; 
 int /*<<< orphan*/  I2C_DMAC_LED_Init () ; 
 int /*<<< orphan*/  I2C_LED_Q_ONOFF (scalar_t__) ; 
 scalar_t__ ISSI3733_DRIVER_COUNT ; 
 int /*<<< orphan*/  SR_EXP_Init () ; 
 scalar_t__ USB2422_Port_Detect_Init () ; 
 int /*<<< orphan*/  USB2422_init () ; 
 scalar_t__ USB_FSMSTATUS_FSMSTATE_SLEEP_Val ; 
 scalar_t__ USB_FSMSTATUS_FSMSTATE_SUSPEND_Val ; 
 int /*<<< orphan*/  adc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_atsam_driver ; 
 int /*<<< orphan*/  debug_code_disable () ; 
 int /*<<< orphan*/  debug_code_init () ; 
 scalar_t__ g_usb_state ; 
 int /*<<< orphan*/  host_set_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c1_init () ; 
 int /*<<< orphan*/  i2c_led_q_init () ; 
 int /*<<< orphan*/  keyboard_init () ; 
 int /*<<< orphan*/  keyboard_setup () ; 
 int /*<<< orphan*/  keyboard_task () ; 
 int /*<<< orphan*/  main_subtasks () ; 
 int /*<<< orphan*/  matrix_init () ; 
 scalar_t__ suspend_wakeup_condition () ; 
 scalar_t__ timer_read64 () ; 
 int /*<<< orphan*/  udc_remotewakeup () ; 
 int /*<<< orphan*/  udc_start () ; 
 int /*<<< orphan*/  v_5v_avg ; 
 int /*<<< orphan*/  wait_ms (int) ; 

int main(void) {
    DBG_LED_ENA;
    DBG_1_ENA;
    DBG_1_OFF;
    DBG_2_ENA;
    DBG_2_OFF;
    DBG_3_ENA;
    DBG_3_OFF;

    debug_code_init();

    CLK_init();

    ADC0_init();

    SR_EXP_Init();

#ifdef RGB_MATRIX_ENABLE
    i2c1_init();
#endif  // RGB_MATRIX_ENABLE

    matrix_init();

    USB2422_init();

    DBGC(DC_MAIN_UDC_START_BEGIN);
    udc_start();
    DBGC(DC_MAIN_UDC_START_COMPLETE);

    DBGC(DC_MAIN_CDC_INIT_BEGIN);
    CDC_init();
    DBGC(DC_MAIN_CDC_INIT_COMPLETE);

    while (USB2422_Port_Detect_Init() == 0) {
    }

    DBG_LED_OFF;

#ifdef RGB_MATRIX_ENABLE
    while (I2C3733_Init_Control() != 1) {
    }
    while (I2C3733_Init_Drivers() != 1) {
    }

    I2C_DMAC_LED_Init();

    i2c_led_q_init();

    for (uint8_t drvid = 0; drvid < ISSI3733_DRIVER_COUNT; drvid++) I2C_LED_Q_ONOFF(drvid);  // Queue data
#endif                                                                                       // RGB_MATRIX_ENABLE

    keyboard_setup();

    keyboard_init();

    host_set_driver(&arm_atsam_driver);

#ifdef CONSOLE_ENABLE
    uint64_t next_print = 0;
#endif  // CONSOLE_ENABLE

    v_5v_avg = adc_get(ADC_5V);

    debug_code_disable();

    while (1) {
        main_subtasks();  // Note these tasks will also be run while waiting for USB keyboard polling intervals

        if (g_usb_state == USB_FSMSTATUS_FSMSTATE_SUSPEND_Val || g_usb_state == USB_FSMSTATUS_FSMSTATE_SLEEP_Val) {
            if (suspend_wakeup_condition()) {
                udc_remotewakeup();  // Send remote wakeup signal
                wait_ms(50);
            }

            continue;
        }

        keyboard_task();

#ifdef CONSOLE_ENABLE
        if (timer_read64() > next_print) {
            next_print = timer_read64() + 250;
            // Add any debug information here that you want to see very often
            // dprintf("5v=%u 5vu=%u dlow=%u dhi=%u gca=%u gcd=%u\r\n", v_5v, v_5v_avg, v_5v_avg - V5_LOW, v_5v_avg - V5_HIGH, gcr_actual, gcr_desired);
        }
#endif  // CONSOLE_ENABLE
    }

    return 1;
}