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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  _delay_ms (int) ; 
 int connected ; 
 int /*<<< orphan*/  iwrap_mux_send (char*) ; 
 int /*<<< orphan*/  rcv_buf ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

uint8_t iwrap_check_connection(void) {
    iwrap_mux_send("LIST");
    _delay_ms(100);

    if (strncmp(rcv_buf, "LIST ", 5) || !strncmp(rcv_buf, "LIST 0", 6))
        connected = 0;
    else
        connected = 1;
    return connected;
}