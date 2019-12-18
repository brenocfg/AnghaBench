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
 int WAITING_BUFFER_SIZE ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug_dec (int) ; 
 int /*<<< orphan*/  debug_record (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * waiting_buffer ; 
 int waiting_buffer_head ; 
 int waiting_buffer_tail ; 

__attribute__((used)) static void debug_waiting_buffer(void) {
    debug("{ ");
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        debug("[");
        debug_dec(i);
        debug("]=");
        debug_record(waiting_buffer[i]);
        debug(" ");
    }
    debug("}\n");
}