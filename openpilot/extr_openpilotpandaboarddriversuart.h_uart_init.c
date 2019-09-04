#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_8__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_9__ {int CR1; int /*<<< orphan*/  CR3; int /*<<< orphan*/  DR; } ;
typedef  TYPE_1__ USART_TypeDef ;
struct TYPE_10__ {int CR; void* PAR; int /*<<< orphan*/  NDTR; void* M0AR; } ;

/* Variables and functions */
 TYPE_8__* DMA2_Stream5 ; 
 int /*<<< orphan*/  DMA2_Stream5_IRQn ; 
 int DMA_SxCR_CHSEL_2 ; 
 int DMA_SxCR_EN ; 
 int DMA_SxCR_HTIE ; 
 int DMA_SxCR_MINC ; 
 int DMA_SxCR_TCIE ; 
 int /*<<< orphan*/  NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 TYPE_1__* UART5 ; 
 int /*<<< orphan*/  UART5_IRQn ; 
 TYPE_1__* USART1 ; 
 int /*<<< orphan*/  USART1_DMA_LEN ; 
 int /*<<< orphan*/  USART1_IRQn ; 
 TYPE_1__* USART2 ; 
 int /*<<< orphan*/  USART2_IRQn ; 
 TYPE_1__* USART3 ; 
 int /*<<< orphan*/  USART3_IRQn ; 
 int USART_CR1_RE ; 
 int USART_CR1_RXNEIE ; 
 int USART_CR1_TE ; 
 int USART_CR1_UE ; 
 int /*<<< orphan*/  USART_CR3_DMAR ; 
 int /*<<< orphan*/  uart_set_baud (TYPE_1__*,int) ; 
 scalar_t__ usart1_dma ; 

void uart_init(USART_TypeDef *u, int baud) {
  // enable uart and tx+rx mode
  u->CR1 = USART_CR1_UE;
  uart_set_baud(u, baud);

  u->CR1 |= USART_CR1_TE | USART_CR1_RE;
  //u->CR2 = USART_CR2_STOP_0 | USART_CR2_STOP_1;
  //u->CR2 = USART_CR2_STOP_0;
  // ** UART is ready to work **

  // enable interrupts
  if (u != USART1) {
    u->CR1 |= USART_CR1_RXNEIE;
  }

  if (u == USART1) {
    // DMA2, stream 2, channel 3
    DMA2_Stream5->M0AR = (uint32_t)usart1_dma;
    DMA2_Stream5->NDTR = USART1_DMA_LEN;
    DMA2_Stream5->PAR = (uint32_t)&(USART1->DR);

    // channel4, increment memory, periph -> memory, enable
    DMA2_Stream5->CR = DMA_SxCR_CHSEL_2 | DMA_SxCR_MINC | DMA_SxCR_HTIE | DMA_SxCR_TCIE | DMA_SxCR_EN;

    // this one uses DMA receiver
    u->CR3 = USART_CR3_DMAR;

    NVIC_EnableIRQ(DMA2_Stream5_IRQn);
    NVIC_EnableIRQ(USART1_IRQn);
  } else if (u == USART2) {
    NVIC_EnableIRQ(USART2_IRQn);
  } else if (u == USART3) {
    NVIC_EnableIRQ(USART3_IRQn);
  } else if (u == UART5) {
    NVIC_EnableIRQ(UART5_IRQn);
  }
}