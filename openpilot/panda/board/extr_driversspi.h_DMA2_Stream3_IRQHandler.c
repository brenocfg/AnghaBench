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
 int /*<<< orphan*/  DMA_LIFCR_CTCIF3 ; 
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  MODE_INPUT ; 
 int /*<<< orphan*/  PULL_UP ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  set_gpio_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gpio_pullup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void DMA2_Stream3_IRQHandler(void) {
  #ifdef DEBUG_SPI
    puts("SPI handshake\n");
  #endif

  // reset handshake back to pull up
  set_gpio_mode(GPIOB, 0, MODE_INPUT);
  set_gpio_pullup(GPIOB, 0, PULL_UP);

  // ack
  DMA2->LIFCR = DMA_LIFCR_CTCIF3;
}