#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ dma_rx; TYPE_2__* uart; } ;
typedef  TYPE_1__ uart_ring ;
struct TYPE_10__ {int CR1; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 TYPE_2__* UART5 ; 
 int /*<<< orphan*/  UART5_IRQn ; 
 TYPE_2__* USART1 ; 
 int /*<<< orphan*/  USART1_IRQn ; 
 TYPE_2__* USART2 ; 
 int /*<<< orphan*/  USART2_IRQn ; 
 TYPE_2__* USART3 ; 
 int /*<<< orphan*/  USART3_IRQn ; 
 int USART_CR1_RE ; 
 int USART_CR1_TE ; 
 int USART_CR1_UE ; 
 int /*<<< orphan*/  dma_rx_init (TYPE_1__*) ; 
 int /*<<< orphan*/  uart_set_baud (TYPE_2__*,int) ; 

void uart_init(uart_ring *q, int baud) {
  // Set baud and enable peripheral with TX and RX mode
  uart_set_baud(q->uart, baud);
  q->uart->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;

  // Enable UART interrupts
  if(q->uart == USART1){
    NVIC_EnableIRQ(USART1_IRQn);
  } else if (q->uart == USART2){
    NVIC_EnableIRQ(USART2_IRQn);
  } else if (q->uart == USART3){
    NVIC_EnableIRQ(USART3_IRQn);
  } else if (q->uart == UART5){
    NVIC_EnableIRQ(UART5_IRQn);
  } else {
    // UART not used. Skip enabling interrupts
  }

  // Initialise RX DMA if used
  if(q->dma_rx){
    dma_rx_init(q);
  }
}