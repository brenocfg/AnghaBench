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
struct TYPE_2__ {unsigned int PR; } ;

/* Variables and functions */
 TYPE_1__* EXTI ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  spi_buf ; 
 int /*<<< orphan*/  spi_rx_dma (int /*<<< orphan*/ ,int) ; 
 scalar_t__ spi_total_count ; 

void EXTI4_IRQHandler(void) {
  volatile unsigned int pr = EXTI->PR & (1U << 4);
  #ifdef DEBUG_SPI
    puts("exti4\n");
  #endif
  // SPI CS falling
  if ((pr & (1U << 4)) != 0U) {
    spi_total_count = 0;
    spi_rx_dma(spi_buf, 0x14);
  }
  EXTI->PR = pr;
}