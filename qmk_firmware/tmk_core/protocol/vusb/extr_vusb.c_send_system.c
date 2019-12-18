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
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {scalar_t__ usage; int /*<<< orphan*/  report_id; } ;
typedef  TYPE_1__ report_extra_t ;
typedef  int /*<<< orphan*/  report ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_ID_SYSTEM ; 
 scalar_t__ usbInterruptIsReady3 () ; 
 int /*<<< orphan*/  usbSetInterrupt3 (void*,int) ; 

__attribute__((used)) static void send_system(uint16_t data) {
    static uint16_t last_data = 0;
    if (data == last_data) return;
    last_data = data;

    report_extra_t report = {.report_id = REPORT_ID_SYSTEM, .usage = data};
    if (usbInterruptIsReady3()) {
        usbSetInterrupt3((void *)&report, sizeof(report));
    }
}