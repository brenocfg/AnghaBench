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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  NEXT_KBD_READ ; 
 int /*<<< orphan*/  query () ; 
 int /*<<< orphan*/  response () ; 
 int /*<<< orphan*/  sei () ; 

uint32_t next_kbd_recv(void) {
    // First check to make sure that the keyboard is actually connected;
    // if not, just return
    // TODO: reflect the status of the keyboard in a return code
    if (!NEXT_KBD_READ) {
        sei();
        return 0;
    }

    query();
    uint32_t resp = response();

    return resp;
}