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
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t RX_BUFFER_SIZE ; 
 size_t* rx_buffer ; 
 int rx_buffer_head ; 
 int rx_buffer_tail ; 

uint8_t uart_getchar(void) {
    uint8_t c, i;

    while (rx_buffer_head == rx_buffer_tail)
        ;  // wait for character
    i = rx_buffer_tail + 1;
    if (i >= RX_BUFFER_SIZE) i = 0;
    c              = rx_buffer[i];
    rx_buffer_tail = i;
    return c;
}