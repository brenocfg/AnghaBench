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
typedef  int /*<<< orphan*/  host_driver_t ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_Init () ; 
 scalar_t__ USB_ACTIVE ; 
 TYPE_1__ USB_DRIVER ; 
 scalar_t__ USB_SUSPENDED ; 
 int /*<<< orphan*/  chSysInit () ; 
 int /*<<< orphan*/  chibios_driver ; 
 int /*<<< orphan*/  console_task () ; 
 int /*<<< orphan*/ * get_serial_link_driver () ; 
 int /*<<< orphan*/  halInit () ; 
 int /*<<< orphan*/  host_set_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_serial_link () ; 
 int /*<<< orphan*/  init_usb_driver (TYPE_1__*) ; 
 scalar_t__ is_serial_link_connected () ; 
 int /*<<< orphan*/  keyboard_init () ; 
 int /*<<< orphan*/  keyboard_setup () ; 
 int /*<<< orphan*/  keyboard_task () ; 
 int /*<<< orphan*/  mousekey_send () ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  raw_hid_task () ; 
 int /*<<< orphan*/  rgblight_task () ; 
 int /*<<< orphan*/  send_keyboard_report () ; 
 int /*<<< orphan*/  sendchar_pf ; 
 int /*<<< orphan*/  serial_link_update () ; 
 int /*<<< orphan*/  setup_midi () ; 
 int /*<<< orphan*/  sleep_led_init () ; 
 int /*<<< orphan*/  suspend_power_down () ; 
 scalar_t__ suspend_wakeup_condition () ; 
 int /*<<< orphan*/  usbWakeupHost (TYPE_1__*) ; 
 int /*<<< orphan*/  virtser_task () ; 
 int /*<<< orphan*/  visualizer_init () ; 
 int /*<<< orphan*/  visualizer_resume () ; 
 int /*<<< orphan*/  visualizer_suspend () ; 
 int /*<<< orphan*/  wait_ms (int) ; 

int main(void) {
    /* ChibiOS/RT init */
    halInit();
    chSysInit();

#ifdef STM32_EEPROM_ENABLE
    EEPROM_Init();
#endif

    // TESTING
    // chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

    keyboard_setup();

    /* Init USB */
    init_usb_driver(&USB_DRIVER);

    /* init printf */
    init_printf(NULL, sendchar_pf);

#ifdef MIDI_ENABLE
    setup_midi();
#endif

#ifdef SERIAL_LINK_ENABLE
    init_serial_link();
#endif

#ifdef VISUALIZER_ENABLE
    visualizer_init();
#endif

    host_driver_t *driver = NULL;

    /* Wait until the USB or serial link is active */
    while (true) {
#if defined(WAIT_FOR_USB) || defined(SERIAL_LINK_ENABLE)
        if (USB_DRIVER.state == USB_ACTIVE) {
            driver = &chibios_driver;
            break;
        }
#else
        driver = &chibios_driver;
        break;
#endif
#ifdef SERIAL_LINK_ENABLE
        if (is_serial_link_connected()) {
            driver = get_serial_link_driver();
            break;
        }
        serial_link_update();
#endif
        wait_ms(50);
    }

    /* Do need to wait here!
     * Otherwise the next print might start a transfer on console EP
     * before the USB is completely ready, which sometimes causes
     * HardFaults.
     */
    wait_ms(50);

    print("USB configured.\n");

    /* init TMK modules */
    keyboard_init();
    host_set_driver(driver);

#ifdef SLEEP_LED_ENABLE
    sleep_led_init();
#endif

    print("Keyboard start.\n");

    /* Main loop */
    while (true) {
#if !defined(NO_USB_STARTUP_CHECK)
        if (USB_DRIVER.state == USB_SUSPENDED) {
            print("[s]");
#    ifdef VISUALIZER_ENABLE
            visualizer_suspend();
#    endif
            while (USB_DRIVER.state == USB_SUSPENDED) {
                /* Do this in the suspended state */
#    ifdef SERIAL_LINK_ENABLE
                serial_link_update();
#    endif
                suspend_power_down();  // on AVR this deep sleeps for 15ms
                /* Remote wakeup */
                if (suspend_wakeup_condition()) {
                    usbWakeupHost(&USB_DRIVER);
                }
            }
            /* Woken up */
            // variables has been already cleared by the wakeup hook
            send_keyboard_report();
#    ifdef MOUSEKEY_ENABLE
            mousekey_send();
#    endif /* MOUSEKEY_ENABLE */

#    ifdef VISUALIZER_ENABLE
            visualizer_resume();
#    endif
        }
#endif

        keyboard_task();
#ifdef CONSOLE_ENABLE
        console_task();
#endif
#ifdef VIRTSER_ENABLE
        virtser_task();
#endif
#ifdef RAW_ENABLE
        raw_hid_task();
#endif
#if defined(RGBLIGHT_ANIMATIONS) && defined(RGBLIGHT_ENABLE)
        rgblight_task();
#endif
    }
}