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

/* Variables and functions */
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  iwrap_mux_send (char*) ; 
 int /*<<< orphan*/  print_S (char*) ; 
 char* rcv_buf ; 
 int rcv_tail ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

void iwrap_unpair(void) {
    iwrap_mux_send("SET BT PAIR");
    _delay_ms(500);

    char *p = rcv_buf + rcv_tail;
    if (!strncmp(p, "SET BT PAIR", 11)) {
        strncpy(p + 29, "\n\0", 2);
        print_S(p);
        iwrap_mux_send(p);
    }
}