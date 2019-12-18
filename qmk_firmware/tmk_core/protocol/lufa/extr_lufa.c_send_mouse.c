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
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {int x; int y; int v; int h; int buttons; } ;
typedef  TYPE_1__ report_mouse_t ;

/* Variables and functions */
 int /*<<< orphan*/  Endpoint_ClearIN () ; 
 int /*<<< orphan*/  Endpoint_IsReadWriteAllowed () ; 
 int /*<<< orphan*/  Endpoint_SelectEndpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Endpoint_Write_Stream_LE (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MOUSE_IN_EPNUM ; 
 scalar_t__ OUTPUT_BLUETOOTH ; 
 scalar_t__ OUTPUT_USB ; 
 scalar_t__ OUTPUT_USB_AND_BT ; 
 int /*<<< orphan*/  _delay_us (int) ; 
 int /*<<< orphan*/  adafruit_ble_send_mouse_move (int,int,int,int,int) ; 
 int /*<<< orphan*/  bluefruit_serial_send (int) ; 
 scalar_t__ where_to_send () ; 

__attribute__((used)) static void send_mouse(report_mouse_t *report) {
#ifdef MOUSE_ENABLE
    uint8_t timeout = 255;
    uint8_t where   = where_to_send();

#    ifdef BLUETOOTH_ENABLE
    if (where == OUTPUT_BLUETOOTH || where == OUTPUT_USB_AND_BT) {
#        ifdef MODULE_ADAFRUIT_BLE
        // FIXME: mouse buttons
        adafruit_ble_send_mouse_move(report->x, report->y, report->v, report->h, report->buttons);
#        else
        bluefruit_serial_send(0xFD);
        bluefruit_serial_send(0x00);
        bluefruit_serial_send(0x03);
        bluefruit_serial_send(report->buttons);
        bluefruit_serial_send(report->x);
        bluefruit_serial_send(report->y);
        bluefruit_serial_send(report->v);  // should try sending the wheel v here
        bluefruit_serial_send(report->h);  // should try sending the wheel h here
        bluefruit_serial_send(0x00);
#        endif
    }
#    endif

    if (where != OUTPUT_USB && where != OUTPUT_USB_AND_BT) {
        return;
    }

    /* Select the Mouse Report Endpoint */
    Endpoint_SelectEndpoint(MOUSE_IN_EPNUM);

    /* Check if write ready for a polling interval around 10ms */
    while (timeout-- && !Endpoint_IsReadWriteAllowed()) _delay_us(40);
    if (!Endpoint_IsReadWriteAllowed()) return;

    /* Write Mouse Report Data */
    Endpoint_Write_Stream_LE(report, sizeof(report_mouse_t), NULL);

    /* Finalize the stream transfer to send the last packet */
    Endpoint_ClearIN();
#endif
}