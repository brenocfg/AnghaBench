#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  usage; int /*<<< orphan*/  report_id; } ;
typedef  TYPE_1__ report_extra_t ;

/* Variables and functions */
 scalar_t__ DEVICE_STATE_Configured ; 
 int /*<<< orphan*/  Endpoint_ClearIN () ; 
 int /*<<< orphan*/  Endpoint_IsReadWriteAllowed () ; 
 int /*<<< orphan*/  Endpoint_SelectEndpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Endpoint_Write_Stream_LE (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REPORT_ID_SYSTEM ; 
 int /*<<< orphan*/  SHARED_IN_EPNUM ; 
 scalar_t__ SYSTEM_POWER_DOWN ; 
 scalar_t__ USB_DeviceState ; 
 int /*<<< orphan*/  _delay_us (int) ; 

__attribute__((used)) static void send_system(uint16_t data) {
#ifdef EXTRAKEY_ENABLE
    uint8_t timeout = 255;

    if (USB_DeviceState != DEVICE_STATE_Configured) return;

    report_extra_t r = {.report_id = REPORT_ID_SYSTEM, .usage = data - SYSTEM_POWER_DOWN + 1};
    Endpoint_SelectEndpoint(SHARED_IN_EPNUM);

    /* Check if write ready for a polling interval around 10ms */
    while (timeout-- && !Endpoint_IsReadWriteAllowed()) _delay_us(40);
    if (!Endpoint_IsReadWriteAllowed()) return;

    Endpoint_Write_Stream_LE(&r, sizeof(report_extra_t), NULL);
    Endpoint_ClearIN();
#endif
}