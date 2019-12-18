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
typedef  size_t uint8_t ;
struct TYPE_3__ {int* raw; } ;
typedef  TYPE_1__ report_keyboard_t ;

/* Variables and functions */
 size_t KEYBOARD_REPORT_SIZE ; 
 int /*<<< orphan*/  bluefruit_serial_send (int) ; 
 int /*<<< orphan*/  bluefruit_trace_footer () ; 
 int /*<<< orphan*/  bluefruit_trace_header () ; 

__attribute__((used)) static void send_keyboard(report_keyboard_t *report) {
#ifdef BLUEFRUIT_TRACE_SERIAL
    bluefruit_trace_header();
#endif
    bluefruit_serial_send(0xFD);
    for (uint8_t i = 0; i < KEYBOARD_REPORT_SIZE; i++) {
        bluefruit_serial_send(report->raw[i]);
    }
#ifdef BLUEFRUIT_TRACE_SERIAL
    bluefruit_trace_footer();
#endif
}