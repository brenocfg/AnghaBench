#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
typedef  TYPE_1__ report_keyboard_t ;
struct TYPE_5__ {int /*<<< orphan*/  nkro; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDI_HID_KBD_REPORT_SIZE ; 
 int /*<<< orphan*/  UDI_HID_NKRO_REPORT_SIZE ; 
 int /*<<< orphan*/  __DMB () ; 
 int /*<<< orphan*/  __disable_irq () ; 
 int /*<<< orphan*/  __get_PRIMASK () ; 
 int /*<<< orphan*/  __set_PRIMASK (int /*<<< orphan*/ ) ; 
 TYPE_3__ keymap_config ; 
 int /*<<< orphan*/  main_subtasks () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ udi_hid_kbd_b_report_trans_ongoing ; 
 int udi_hid_kbd_b_report_valid ; 
 int /*<<< orphan*/  udi_hid_kbd_report ; 
 int /*<<< orphan*/  udi_hid_kbd_send_report () ; 
 scalar_t__ udi_hid_nkro_b_report_trans_ongoing ; 
 int udi_hid_nkro_b_report_valid ; 
 int /*<<< orphan*/  udi_hid_nkro_report ; 
 int /*<<< orphan*/  udi_hid_nkro_send_report () ; 

void send_keyboard(report_keyboard_t *report) {
    uint32_t irqflags;

#ifdef NKRO_ENABLE
    if (!keymap_config.nkro) {
#endif  // NKRO_ENABLE
        while (udi_hid_kbd_b_report_trans_ongoing) {
            main_subtasks();
        }  // Run other tasks while waiting for USB to be free

        irqflags = __get_PRIMASK();
        __disable_irq();
        __DMB();

        memcpy(udi_hid_kbd_report, report->raw, UDI_HID_KBD_REPORT_SIZE);
        udi_hid_kbd_b_report_valid = 1;
        udi_hid_kbd_send_report();

        __DMB();
        __set_PRIMASK(irqflags);
#ifdef NKRO_ENABLE
    } else {
        while (udi_hid_nkro_b_report_trans_ongoing) {
            main_subtasks();
        }  // Run other tasks while waiting for USB to be free

        irqflags = __get_PRIMASK();
        __disable_irq();
        __DMB();

        memcpy(udi_hid_nkro_report, report->raw, UDI_HID_NKRO_REPORT_SIZE);
        udi_hid_nkro_b_report_valid = 1;
        udi_hid_nkro_send_report();

        __DMB();
        __set_PRIMASK(irqflags);
    }
#endif  // NKRO_ENABLE
}