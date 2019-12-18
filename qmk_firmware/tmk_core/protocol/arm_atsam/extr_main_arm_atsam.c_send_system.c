#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {scalar_t__ report_data; int /*<<< orphan*/  report_id; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_ID_SYSTEM ; 
 scalar_t__ SYSTEM_POWER_DOWN ; 
 int /*<<< orphan*/  __DMB () ; 
 int /*<<< orphan*/  __disable_irq () ; 
 int /*<<< orphan*/  __get_PRIMASK () ; 
 int /*<<< orphan*/  __set_PRIMASK (int /*<<< orphan*/ ) ; 
 int udi_hid_exk_b_report_valid ; 
 TYPE_2__ udi_hid_exk_report ; 
 int /*<<< orphan*/  udi_hid_exk_send_report () ; 

void send_system(uint16_t data) {
#ifdef EXTRAKEY_ENABLE
    uint32_t irqflags;

    irqflags = __get_PRIMASK();
    __disable_irq();
    __DMB();

    udi_hid_exk_report.desc.report_id = REPORT_ID_SYSTEM;
    if (data != 0) data = data - SYSTEM_POWER_DOWN + 1;
    udi_hid_exk_report.desc.report_data = data;
    udi_hid_exk_b_report_valid          = 1;
    udi_hid_exk_send_report();

    __DMB();
    __set_PRIMASK(irqflags);
#endif  // EXTRAKEY_ENABLE
}