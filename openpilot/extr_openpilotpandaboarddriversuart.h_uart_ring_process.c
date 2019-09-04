#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_7__ {size_t w_ptr_tx; size_t r_ptr_tx; int w_ptr_rx; scalar_t__ r_ptr_rx; int /*<<< orphan*/  (* callback ) (TYPE_2__*) ;int /*<<< orphan*/ * elems_rx; TYPE_1__* uart; int /*<<< orphan*/ * elems_tx; } ;
typedef  TYPE_2__ uart_ring ;
struct TYPE_6__ {int SR; int /*<<< orphan*/  DR; int /*<<< orphan*/  CR1; } ;

/* Variables and functions */
 int FIFO_SIZE ; 
 int /*<<< orphan*/  USART_CR1_TXEIE ; 
 int USART_SR_ORE ; 
 int USART_SR_RXNE ; 
 int USART_SR_TXE ; 
 int /*<<< orphan*/  enter_critical_section () ; 
 TYPE_2__ esp_ring ; 
 int /*<<< orphan*/  exit_critical_section () ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void uart_ring_process(uart_ring *q) {
  enter_critical_section();
  // TODO: check if external serial is connected
  int sr = q->uart->SR;

  if (q->w_ptr_tx != q->r_ptr_tx) {
    if (sr & USART_SR_TXE) {
      q->uart->DR = q->elems_tx[q->r_ptr_tx];
      q->r_ptr_tx = (q->r_ptr_tx + 1) % FIFO_SIZE;
    } else {
      // push on interrupt later
      q->uart->CR1 |= USART_CR1_TXEIE;
    }
  } else {
    // nothing to send
    q->uart->CR1 &= ~USART_CR1_TXEIE;
  }

  if (sr & USART_SR_RXNE || sr & USART_SR_ORE) {
    uint8_t c = q->uart->DR;  // TODO: can drop packets
    if (q != &esp_ring) {
      uint16_t next_w_ptr = (q->w_ptr_rx + 1) % FIFO_SIZE;
      if (next_w_ptr != q->r_ptr_rx) {
        q->elems_rx[q->w_ptr_rx] = c;
        q->w_ptr_rx = next_w_ptr;
        if (q->callback) q->callback(q);
      }
    }
  }

  if (sr & USART_SR_ORE) {
    // set dropped packet flag?
  }

  exit_critical_section();
}