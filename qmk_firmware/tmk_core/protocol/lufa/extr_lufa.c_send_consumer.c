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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {scalar_t__ usage; int /*<<< orphan*/  report_id; } ;
typedef  TYPE_1__ report_extra_t ;

/* Variables and functions */
 scalar_t__ CONSUMER2BLUEFRUIT (scalar_t__) ; 
 scalar_t__ CONSUMER2RN42 (scalar_t__) ; 
 int /*<<< orphan*/  Endpoint_ClearIN () ; 
 int /*<<< orphan*/  Endpoint_IsReadWriteAllowed () ; 
 int /*<<< orphan*/  Endpoint_SelectEndpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Endpoint_Write_Stream_LE (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ OUTPUT_BLUETOOTH ; 
 scalar_t__ OUTPUT_USB ; 
 scalar_t__ OUTPUT_USB_AND_BT ; 
 int /*<<< orphan*/  REPORT_ID_CONSUMER ; 
 int /*<<< orphan*/  SHARED_IN_EPNUM ; 
 int /*<<< orphan*/  _delay_us (int) ; 
 int /*<<< orphan*/  adafruit_ble_send_consumer_key (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bluefruit_serial_send (int) ; 
 scalar_t__ where_to_send () ; 

__attribute__((used)) static void send_consumer(uint16_t data) {
#ifdef EXTRAKEY_ENABLE
    uint8_t timeout = 255;
    uint8_t where   = where_to_send();

#    ifdef BLUETOOTH_ENABLE
    if (where == OUTPUT_BLUETOOTH || where == OUTPUT_USB_AND_BT) {
#        ifdef MODULE_ADAFRUIT_BLE
        adafruit_ble_send_consumer_key(data, 0);
#        elif MODULE_RN42
        static uint16_t last_data = 0;
        if (data == last_data) return;
        last_data       = data;
        uint16_t bitmap = CONSUMER2RN42(data);
        bluefruit_serial_send(0xFD);
        bluefruit_serial_send(0x03);
        bluefruit_serial_send(0x03);
        bluefruit_serial_send(bitmap & 0xFF);
        bluefruit_serial_send((bitmap >> 8) & 0xFF);
#        else
        static uint16_t last_data = 0;
        if (data == last_data) return;
        last_data       = data;
        uint16_t bitmap = CONSUMER2BLUEFRUIT(data);
        bluefruit_serial_send(0xFD);
        bluefruit_serial_send(0x00);
        bluefruit_serial_send(0x02);
        bluefruit_serial_send((bitmap >> 8) & 0xFF);
        bluefruit_serial_send(bitmap & 0xFF);
        bluefruit_serial_send(0x00);
        bluefruit_serial_send(0x00);
        bluefruit_serial_send(0x00);
        bluefruit_serial_send(0x00);
#        endif
    }
#    endif

    if (where != OUTPUT_USB && where != OUTPUT_USB_AND_BT) {
        return;
    }

    report_extra_t r = {.report_id = REPORT_ID_CONSUMER, .usage = data};
    Endpoint_SelectEndpoint(SHARED_IN_EPNUM);

    /* Check if write ready for a polling interval around 10ms */
    while (timeout-- && !Endpoint_IsReadWriteAllowed()) _delay_us(40);
    if (!Endpoint_IsReadWriteAllowed()) return;

    Endpoint_Write_Stream_LE(&r, sizeof(report_extra_t), NULL);
    Endpoint_ClearIN();
#endif
}