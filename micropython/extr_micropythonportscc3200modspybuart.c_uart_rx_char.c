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
struct TYPE_3__ {size_t read_buf_tail; size_t read_buf_head; int* read_buf; int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ pyb_uart_obj_t ;

/* Variables and functions */
 int MAP_UARTCharGetNonBlocking (int /*<<< orphan*/ ) ; 
 int PYBUART_RX_BUFFER_LEN ; 

int uart_rx_char(pyb_uart_obj_t *self) {
    if (self->read_buf_tail != self->read_buf_head) {
        // buffering via irq
        int data = self->read_buf[self->read_buf_tail];
        self->read_buf_tail = (self->read_buf_tail + 1) % PYBUART_RX_BUFFER_LEN;
        return data;
    } else {
        // no buffering
        return MAP_UARTCharGetNonBlocking(self->reg);
    }
}