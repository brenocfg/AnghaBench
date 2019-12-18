#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned int uint16_t ;
struct TYPE_6__ {int dma_rx; unsigned int w_ptr_rx; unsigned int rx_fifo_size; unsigned int r_ptr_rx; int /*<<< orphan*/  (* callback ) (TYPE_2__*) ;int /*<<< orphan*/ * elems_rx; TYPE_1__* uart; } ;
typedef  TYPE_2__ uart_ring ;
struct TYPE_5__ {int /*<<< orphan*/  DR; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_CRITICAL () ; 
 int /*<<< orphan*/  EXIT_CRITICAL () ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void uart_rx_ring(uart_ring *q){
  // Do not read out directly if DMA enabled
  if (q->dma_rx == false) {
    ENTER_CRITICAL();

    // Read out RX buffer
    uint8_t c = q->uart->DR;  // This read after reading SR clears a bunch of interrupts

    uint16_t next_w_ptr = (q->w_ptr_rx + 1U) % q->rx_fifo_size;
    // Do not overwrite buffer data
    if (next_w_ptr != q->r_ptr_rx) {
      q->elems_rx[q->w_ptr_rx] = c;
      q->w_ptr_rx = next_w_ptr;
      if (q->callback != NULL) {
        q->callback(q);
      }
    }

    EXIT_CRITICAL();
  }
}