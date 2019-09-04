#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_7__ {int w_ptr_rx; int r_ptr_rx; char* elems_rx; TYPE_1__* uart; } ;
typedef  TYPE_2__ uart_ring ;
struct TYPE_9__ {int HISR; int HIFCR; } ;
struct TYPE_8__ {scalar_t__ NDTR; int CR; } ;
struct TYPE_6__ {int /*<<< orphan*/  CR3; } ;

/* Variables and functions */
 TYPE_5__* DMA2 ; 
 TYPE_4__* DMA2_Stream5 ; 
 int DMA_HIFCR_CHTIF5 ; 
 int DMA_HIFCR_CTCIF5 ; 
 int DMA_HISR_HTIF5 ; 
 int DMA_HISR_TCIF5 ; 
 int DMA_SxCR_EN ; 
 int FIFO_SIZE ; 
 scalar_t__ USART1_DMA_LEN ; 
 int /*<<< orphan*/  USART_CR3_DMAR ; 
 int /*<<< orphan*/  enter_critical_section () ; 
 TYPE_2__ esp_ring ; 
 int /*<<< orphan*/  exit_critical_section () ; 
 char* usart1_dma ; 

void uart_dma_drain() {
  uart_ring *q = &esp_ring;

  enter_critical_section();

  if (DMA2->HISR & DMA_HISR_TCIF5 || DMA2->HISR & DMA_HISR_HTIF5 || DMA2_Stream5->NDTR != USART1_DMA_LEN) {
    // disable DMA
    q->uart->CR3 &= ~USART_CR3_DMAR;
    DMA2_Stream5->CR &= ~DMA_SxCR_EN;
    while (DMA2_Stream5->CR & DMA_SxCR_EN);

    int i;
    for (i = 0; i < USART1_DMA_LEN - DMA2_Stream5->NDTR; i++) {
      char c = usart1_dma[i];
      uint16_t next_w_ptr = (q->w_ptr_rx + 1) % FIFO_SIZE;
      if (next_w_ptr != q->r_ptr_rx) {
        q->elems_rx[q->w_ptr_rx] = c;
        q->w_ptr_rx = next_w_ptr;
      }
    }

    // reset DMA len
    DMA2_Stream5->NDTR = USART1_DMA_LEN;

    // clear interrupts
    DMA2->HIFCR = DMA_HIFCR_CTCIF5 | DMA_HIFCR_CHTIF5;
    //DMA2->HIFCR = DMA_HIFCR_CTEIF5 | DMA_HIFCR_CDMEIF5 | DMA_HIFCR_CFEIF5;

    // enable DMA
    DMA2_Stream5->CR |= DMA_SxCR_EN;
    q->uart->CR3 |= USART_CR3_DMAR;
  }

  exit_critical_section();
}