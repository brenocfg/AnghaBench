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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_hex8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  serial_send (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bluefruit_serial_send(uint8_t data) {
#ifdef BLUEFRUIT_TRACE_SERIAL
    dprintf(" ");
    debug_hex8(data);
    dprintf(" ");
#endif
    serial_send(data);
}