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
typedef  void* uint32_t ;
struct TYPE_4__ {int CR; int NDTR; void* PAR; void* M0AR; } ;
struct TYPE_3__ {int /*<<< orphan*/  CR2; int /*<<< orphan*/  DR; } ;

/* Variables and functions */
 TYPE_2__* DMA2_Stream3 ; 
 int DMA_SxCR_CHSEL_0 ; 
 int DMA_SxCR_CHSEL_1 ; 
 int DMA_SxCR_DIR_0 ; 
 int DMA_SxCR_EN ; 
 int DMA_SxCR_MINC ; 
 int DMA_SxCR_TCIE ; 
 int /*<<< orphan*/  GPIOB ; 
 TYPE_1__* SPI1 ; 
 int /*<<< orphan*/  SPI_CR2_TXDMAEN ; 
 int /*<<< orphan*/  delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gpio_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void spi_tx_dma(void *addr, int len) {
  // disable DMA
  SPI1->CR2 &= ~SPI_CR2_TXDMAEN;
  DMA2_Stream3->CR &= ~DMA_SxCR_EN;

  // DMA2, stream 3, channel 3
  DMA2_Stream3->M0AR = (uint32_t)addr;
  DMA2_Stream3->NDTR = len;
  DMA2_Stream3->PAR = (uint32_t)&(SPI1->DR);

  // channel3, increment memory, memory -> periph, enable
  DMA2_Stream3->CR = DMA_SxCR_CHSEL_1 | DMA_SxCR_CHSEL_0 | DMA_SxCR_MINC | DMA_SxCR_DIR_0 | DMA_SxCR_EN;
  delay(0);
  DMA2_Stream3->CR |= DMA_SxCR_TCIE;

  SPI1->CR2 |= SPI_CR2_TXDMAEN;

  // signal data is ready by driving low
  // esp must be configured as input by this point
  set_gpio_output(GPIOB, 0, 0);
}