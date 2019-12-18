#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_8__ {TYPE_1__* uart; int /*<<< orphan*/  rx_fifo_size; scalar_t__ elems_rx; } ;
typedef  TYPE_2__ uart_ring ;
struct TYPE_10__ {int CR; int /*<<< orphan*/  NDTR; void* M0AR; void* PAR; int /*<<< orphan*/  FCR; } ;
struct TYPE_9__ {int /*<<< orphan*/  DR; } ;
struct TYPE_7__ {int /*<<< orphan*/  CR1; int /*<<< orphan*/  CR3; } ;

/* Variables and functions */
 TYPE_6__* DMA2_Stream5 ; 
 int /*<<< orphan*/  DMA2_Stream5_IRQn ; 
 int DMA_SxCR_CHSEL_2 ; 
 int DMA_SxCR_CIRC ; 
 int DMA_SxCR_DMEIE ; 
 int DMA_SxCR_EN ; 
 int DMA_SxCR_HTIE ; 
 int DMA_SxCR_MINC ; 
 int DMA_SxCR_TCIE ; 
 int DMA_SxCR_TEIE ; 
 int /*<<< orphan*/  DMA_SxFCR_DMDIS ; 
 int /*<<< orphan*/  NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 TYPE_5__* USART1 ; 
 int /*<<< orphan*/  USART_CR1_IDLEIE ; 
 int /*<<< orphan*/  USART_CR3_DMAR ; 
 int /*<<< orphan*/  puts (char*) ; 
 TYPE_2__ uart_ring_esp_gps ; 

void dma_rx_init(uart_ring *q) {
  // Initialization is UART-dependent
  if(q == &uart_ring_esp_gps){
    // DMA2, stream 5, channel 4

    // Disable FIFO mode (enable direct)
    DMA2_Stream5->FCR &= ~DMA_SxFCR_DMDIS;

    // Setup addresses
    DMA2_Stream5->PAR = (uint32_t)&(USART1->DR);    // Source
    DMA2_Stream5->M0AR = (uint32_t)q->elems_rx;     // Destination
    DMA2_Stream5->NDTR = q->rx_fifo_size;           // Number of bytes to copy

    // Circular, Increment memory, byte size, periph -> memory, enable
    // Transfer complete, half transfer, transfer error and direct mode error interrupt enable
    DMA2_Stream5->CR = DMA_SxCR_CHSEL_2 | DMA_SxCR_MINC | DMA_SxCR_CIRC | DMA_SxCR_HTIE | DMA_SxCR_TCIE | DMA_SxCR_TEIE | DMA_SxCR_DMEIE | DMA_SxCR_EN;
    
    // Enable DMA receiver in UART
    q->uart->CR3 |= USART_CR3_DMAR;

    // Enable UART IDLE interrupt
    q->uart->CR1 |= USART_CR1_IDLEIE;

    // Enable interrupt
    NVIC_EnableIRQ(DMA2_Stream5_IRQn);
  } else {
    puts("Tried to initialize RX DMA for an unsupported UART\n");
  }
}