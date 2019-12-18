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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ CONSUMER2BLUEFRUIT (scalar_t__) ; 
 int /*<<< orphan*/  bluefruit_serial_send (int) ; 
 int /*<<< orphan*/  bluefruit_trace_footer () ; 
 int /*<<< orphan*/  bluefruit_trace_header () ; 
 int /*<<< orphan*/  debug_hex16 (scalar_t__) ; 
 int /*<<< orphan*/  dprintf (char*) ; 

__attribute__((used)) static void send_consumer(uint16_t data) {
    static uint16_t last_data = 0;
    if (data == last_data) return;
    last_data = data;

    uint16_t bitmap = CONSUMER2BLUEFRUIT(data);

#ifdef BLUEFRUIT_TRACE_SERIAL
    dprintf("\nData: ");
    debug_hex16(data);
    dprintf("; bitmap: ");
    debug_hex16(bitmap);
    dprintf("\n");
    bluefruit_trace_header();
#endif
    bluefruit_serial_send(0xFD);
    bluefruit_serial_send(0x00);
    bluefruit_serial_send(0x02);
    bluefruit_serial_send((bitmap >> 8) & 0xFF);
    bluefruit_serial_send(bitmap & 0xFF);
    bluefruit_serial_send(0x00);
    bluefruit_serial_send(0x00);
    bluefruit_serial_send(0x00);
    bluefruit_serial_send(0x00);
#ifdef BLUEFRUIT_TRACE_SERIAL
    bluefruit_trace_footer();
#endif
}