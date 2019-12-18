#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {size_t read_buf_tail; size_t read_buf_head; scalar_t__ char_width; int* read_buf; int read_buf_len; int char_mask; TYPE_3__* uartx; } ;
typedef  TYPE_1__ pyb_uart_obj_t ;
struct TYPE_6__ {int RDR; int DR; int /*<<< orphan*/  ICR; } ;

/* Variables and functions */
 scalar_t__ CHAR_WIDTH_9BIT ; 
 scalar_t__ UART_RXNE_IS_SET (TYPE_3__*) ; 
 int /*<<< orphan*/  UART_RXNE_IT_EN (TYPE_3__*) ; 
 int /*<<< orphan*/  USART_ICR_ORECF ; 

int uart_rx_char(pyb_uart_obj_t *self) {
    if (self->read_buf_tail != self->read_buf_head) {
        // buffering via IRQ
        int data;
        if (self->char_width == CHAR_WIDTH_9BIT) {
            data = ((uint16_t*)self->read_buf)[self->read_buf_tail];
        } else {
            data = self->read_buf[self->read_buf_tail];
        }
        self->read_buf_tail = (self->read_buf_tail + 1) % self->read_buf_len;
        if (UART_RXNE_IS_SET(self->uartx)) {
            // UART was stalled by flow ctrl: re-enable IRQ now we have room in buffer
            UART_RXNE_IT_EN(self->uartx);
        }
        return data;
    } else {
        // no buffering
        #if defined(STM32F0) || defined(STM32F7) || defined(STM32L0) || defined(STM32L4) || defined(STM32H7) || defined(STM32WB)
        int data = self->uartx->RDR & self->char_mask;
        self->uartx->ICR = USART_ICR_ORECF; // clear ORE if it was set
        return data;
        #else
        return self->uartx->DR & self->char_mask;
        #endif
    }
}