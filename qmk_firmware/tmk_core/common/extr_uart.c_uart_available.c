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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ RX_BUFFER_SIZE ; 
 scalar_t__ rx_buffer_head ; 
 scalar_t__ rx_buffer_tail ; 

uint8_t uart_available(void) {
    uint8_t head, tail;

    head = rx_buffer_head;
    tail = rx_buffer_tail;
    if (head >= tail) return head - tail;
    return RX_BUFFER_SIZE + head - tail;
}