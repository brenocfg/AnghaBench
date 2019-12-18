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
typedef  int /*<<< orphan*/  report_keyboard_t ;
typedef  scalar_t__ int8_t ;
struct TYPE_2__ {scalar_t__ nkro; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBD2_ENDPOINT ; 
 int /*<<< orphan*/  KBD2_SIZE ; 
 int /*<<< orphan*/  KBD_ENDPOINT ; 
 int /*<<< orphan*/  KBD_SIZE ; 
 TYPE_1__ keymap_config ; 
 scalar_t__ send_report (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_keyboard_idle_count ; 
 int /*<<< orphan*/  usb_keyboard_print_report (int /*<<< orphan*/ *) ; 

int8_t usb_keyboard_send_report(report_keyboard_t *report) {
    int8_t result = 0;

#ifdef NKRO_ENABLE
    if (keymap_config.nkro)
        result = send_report(report, KBD2_ENDPOINT, 0, KBD2_SIZE);
    else
#endif
    {
        result = send_report(report, KBD_ENDPOINT, 0, KBD_SIZE);
    }

    if (result) return result;
    usb_keyboard_idle_count = 0;
    usb_keyboard_print_report(report);
    return 0;
}