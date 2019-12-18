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
 int RXCIE0 ; 
 int RXEN0 ; 
 int TXEN0 ; 
 size_t TX_BUFFER_SIZE ; 
 int UCSR0B ; 
 int UDRIE0 ; 
 size_t* tx_buffer ; 
 int tx_buffer_head ; 
 size_t tx_buffer_tail ; 

void uart_putchar(uint8_t c) {
    uint8_t i;

    i = tx_buffer_head + 1;
    if (i >= TX_BUFFER_SIZE) i = 0;
    while (tx_buffer_tail == i)
        ;  // wait until space in buffer
    // cli();
    tx_buffer[i]   = c;
    tx_buffer_head = i;
    UCSR0B         = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0) | (1 << UDRIE0);
    // sei();
}