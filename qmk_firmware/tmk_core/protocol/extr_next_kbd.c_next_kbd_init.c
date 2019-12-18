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
 int NEXT_KBD_IN_BIT ; 
 int NEXT_KBD_IN_DDR ; 
 int NEXT_KBD_IN_PORT ; 
 int /*<<< orphan*/  out_hi () ; 
 int /*<<< orphan*/  query_delay (int) ; 
 int /*<<< orphan*/  reset_delay (int) ; 

void next_kbd_init(void) {
    out_hi();
    NEXT_KBD_IN_DDR &= ~(1 << NEXT_KBD_IN_BIT);  // KBD_IN  to input
    NEXT_KBD_IN_PORT |= (1 << NEXT_KBD_IN_BIT);  // KBD_IN  pull up

    query_delay(5);
    reset_delay(8);

    query_delay(5);
    reset_delay(8);
}