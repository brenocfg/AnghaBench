#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {scalar_t__ pressed; } ;
struct TYPE_4__ {TYPE_1__ event; } ;

/* Variables and functions */
 int WAITING_BUFFER_SIZE ; 
 TYPE_2__* waiting_buffer ; 
 int waiting_buffer_head ; 
 int waiting_buffer_tail ; 

__attribute__((unused)) bool waiting_buffer_has_anykey_pressed(void) {
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        if (waiting_buffer[i].event.pressed) return true;
    }
    return false;
}