#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int int16_t ;
struct TYPE_2__ {int nkro; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CHARGER ; 
 int /*<<< orphan*/  LED_ON ; 
 scalar_t__ LOW_VOLTAGE ; 
 int /*<<< orphan*/  battery_led (int /*<<< orphan*/ ) ; 
 scalar_t__ battery_status () ; 
 int battery_voltage () ; 
 int /*<<< orphan*/  clear_keyboard () ; 
 int /*<<< orphan*/  config_mode ; 
 int /*<<< orphan*/  dprintf (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  force_usb ; 
 int /*<<< orphan*/ * host_get_driver () ; 
 int /*<<< orphan*/  host_set_driver (int /*<<< orphan*/ *) ; 
 TYPE_1__ keymap_config ; 
 int /*<<< orphan*/  lufa_driver ; 
 int /*<<< orphan*/  rn42_driver ; 
 int rn42_getc () ; 
 scalar_t__ rn42_linked () ; 
 int rn42_nkro_last ; 
 int /*<<< orphan*/  rn42_rts () ; 
 int /*<<< orphan*/  rn42_set_leds (int) ; 
 int /*<<< orphan*/  status_led (int) ; 
 int timer_elapsed (int) ; 
 int timer_read32 () ; 
 int /*<<< orphan*/  xprintf (char*,int) ; 

void rn42_task(void)
{
    int16_t c;
    // Raw mode: interpret output report of LED state
    while ((c = rn42_getc()) != -1) {
        // LED Out report: 0xFE, 0x02, 0x01, <leds>
        // To get the report over UART set bit3 with SH, command.
        static enum {LED_INIT, LED_FE, LED_02, LED_01} state = LED_INIT;
        switch (state) {
            case LED_INIT:
                if (c == 0xFE) state = LED_FE;
                else {
                    if (0x0 <= c && c <= 0x7f) xprintf("%c", c);
                    else xprintf(" %02X", c);
                }
                break;
            case LED_FE:
                if (c == 0x02) state = LED_02;
                else           state = LED_INIT;
                break;
            case LED_02:
                if (c == 0x01) state = LED_01;
                else           state = LED_INIT;
                break;
            case LED_01:
                dprintf("LED status: %02X\n", c);
                rn42_set_leds(c);
                state = LED_INIT;
                break;
            default:
                state = LED_INIT;
        }
    }

    /* Switch between USB and Bluetooth */
    if (!config_mode) { // not switch while config mode
        if (!force_usb && !rn42_rts()) {
            if (host_get_driver() != &rn42_driver) {
                clear_keyboard();
#ifdef NKRO_ENABLE
                rn42_nkro_last = keymap_config.nkro;
                keymap_config.nkro = false;
#endif
                host_set_driver(&rn42_driver);
            }
        } else {
            if (host_get_driver() != &lufa_driver) {
                clear_keyboard();
#ifdef NKRO_ENABLE
                keymap_config.nkro = rn42_nkro_last;
#endif
                host_set_driver(&lufa_driver);
            }
        }
    }


    static uint16_t prev_timer = 0;
    uint16_t e = timer_elapsed(prev_timer);
    if (e > 1000) {
        /* every second */
        prev_timer += e/1000*1000;

        /* Low voltage alert */
        uint8_t bs = battery_status();
        if (bs == LOW_VOLTAGE) {
            battery_led(LED_ON);
        } else {
            battery_led(LED_CHARGER);
        }

        /* every minute */
        uint32_t t = timer_read32()/1000;
        if (t%60 == 0) {
            uint16_t v = battery_voltage();
            uint8_t h = t/3600;
            uint8_t m = t%3600/60;
            uint8_t s = t%60;
            dprintf("%02u:%02u:%02u\t%umV\n", h, m, s, v);
            /* TODO: xprintf doesn't work for this.
            xprintf("%02u:%02u:%02u\t%umV\n", (t/3600), (t%3600/60), (t%60), v);
            */
        }
    }


    /* Connection monitor */
    if (!rn42_rts() && rn42_linked()) {
        status_led(true);
    } else {
        status_led(false);
    }
}