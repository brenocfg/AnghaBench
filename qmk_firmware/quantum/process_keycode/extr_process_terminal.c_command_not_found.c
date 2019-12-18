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
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 int /*<<< orphan*/  buffer ; 
 int /*<<< orphan*/  send_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void command_not_found(void) {
    wait_ms(50);  // sometimes buffer isnt grabbed quick enough
    SEND_STRING("command \"");
    send_string(buffer);
    SEND_STRING("\" not found\n");
}