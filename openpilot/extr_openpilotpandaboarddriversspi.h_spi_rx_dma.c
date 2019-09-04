#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint32_t ;
struct TYPE_4__ {int CR; int NDTR; void* PAR; void* M0AR; } ;
struct TYPE_3__ {int /*<<< orphan*/  CR2; int /*<<< orphan*/  DR; } ;

/* Variables and functions */
 TYPE_2__* DMA2_Stream2 ; 
 int DMA_SxCR_CHSEL_0 ; 
 int DMA_SxCR_CHSEL_1 ; 
 int DMA_SxCR_EN ; 
 int DMA_SxCR_MINC ; 
 int DMA_SxCR_TCIE ; 
 TYPE_1__* SPI1 ; 
 int /*<<< orphan*/  SPI_CR2_RXDMAEN ; 
 int /*<<< orphan*/  delay (int /*<<< orphan*/ ) ; 

void spi_rx_dma(void *addr, int len) {
  // disable DMA
  SPI1->CR2 &= ~SPI_CR2_RXDMAEN;
  DMA2_Stream2->CR &= ~DMA_SxCR_EN;

  // drain the bus
  volatile uint8_t dat = SPI1->DR;
  (void)dat;

  // DMA2, stream 2, channel 3
  DMA2_Stream2->M0AR = (uint32_t)addr;
  DMA2_Stream2->NDTR = len;
  DMA2_Stream2->PAR = (uint32_t)&(SPI1->DR);

  // channel3, increment memory, periph -> memory, enable
  DMA2_Stream2->CR = DMA_SxCR_CHSEL_1 | DMA_SxCR_CHSEL_0 | DMA_SxCR_MINC | DMA_SxCR_EN;
  delay(0);
  DMA2_Stream2->CR |= DMA_SxCR_TCIE;

  SPI1->CR2 |= SPI_CR2_RXDMAEN;
}