#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ read_buf_tail; scalar_t__ read_buf_head; int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ pyb_uart_obj_t ;

/* Variables and functions */
 scalar_t__ MAP_UARTCharsAvail (int /*<<< orphan*/ ) ; 
 int PYBUART_RX_BUFFER_LEN ; 

uint32_t uart_rx_any(pyb_uart_obj_t *self) {
    if (self->read_buf_tail != self->read_buf_head) {
        // buffering  via irq
        return (self->read_buf_head > self->read_buf_tail) ? self->read_buf_head - self->read_buf_tail :
                PYBUART_RX_BUFFER_LEN - self->read_buf_tail + self->read_buf_head;
    }
    return MAP_UARTCharsAvail(self->reg) ? 1 : 0;
}