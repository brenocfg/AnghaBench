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
struct TYPE_3__ {size_t read_buf_len; int /*<<< orphan*/  uartx; void* read_buf; scalar_t__ read_buf_tail; scalar_t__ read_buf_head; } ;
typedef  TYPE_1__ pyb_uart_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  UART_RXNE_IT_DIS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_RXNE_IT_EN (int /*<<< orphan*/ ) ; 

void uart_set_rxbuf(pyb_uart_obj_t *self, size_t len, void *buf) {
    self->read_buf_head = 0;
    self->read_buf_tail = 0;
    self->read_buf_len = len;
    self->read_buf = buf;
    if (len == 0) {
        UART_RXNE_IT_DIS(self->uartx);
    } else {
        UART_RXNE_IT_EN(self->uartx);
    }
}