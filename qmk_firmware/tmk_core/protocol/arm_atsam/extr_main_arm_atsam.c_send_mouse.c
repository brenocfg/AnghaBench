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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  report_mouse_t ;

/* Variables and functions */
 int /*<<< orphan*/  UDI_HID_MOU_REPORT_SIZE ; 
 int /*<<< orphan*/  __DMB () ; 
 int /*<<< orphan*/  __disable_irq () ; 
 int /*<<< orphan*/  __get_PRIMASK () ; 
 int /*<<< orphan*/  __set_PRIMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int udi_hid_mou_b_report_valid ; 
 int /*<<< orphan*/  udi_hid_mou_report ; 
 int /*<<< orphan*/  udi_hid_mou_send_report () ; 

void send_mouse(report_mouse_t *report) {
#ifdef MOUSEKEY_ENABLE
    uint32_t irqflags;

    irqflags = __get_PRIMASK();
    __disable_irq();
    __DMB();

    memcpy(udi_hid_mou_report, report, UDI_HID_MOU_REPORT_SIZE);
    udi_hid_mou_b_report_valid = 1;
    udi_hid_mou_send_report();

    __DMB();
    __set_PRIMASK(irqflags);
#endif  // MOUSEKEY_ENABLE
}