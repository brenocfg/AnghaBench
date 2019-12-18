#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  LIFCR; } ;

/* Variables and functions */
 TYPE_1__* DMA2 ; 
 int /*<<< orphan*/  DMA_LIFCR_CTCIF2 ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 
 int /*<<< orphan*/  puth (int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  spi_buf ; 
 int spi_cb_rx (int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ spi_tx_buf ; 
 int /*<<< orphan*/  spi_tx_dma (scalar_t__,int) ; 

void DMA2_Stream2_IRQHandler(void) {
  int *resp_len = (int*)spi_tx_buf;
  (void)memset(spi_tx_buf, 0xaa, 0x44);
  *resp_len = spi_cb_rx(spi_buf, 0x14, spi_tx_buf+4);
  #ifdef DEBUG_SPI
    puts("SPI write: ");
    puth(*resp_len);
    puts("\n");
  #endif
  spi_tx_dma(spi_tx_buf, *resp_len + 4);

  // ack
  DMA2->LIFCR = DMA_LIFCR_CTCIF2;
}