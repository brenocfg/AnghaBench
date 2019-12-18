#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int IMR; unsigned int FTSR; } ;
struct TYPE_5__ {int /*<<< orphan*/  CR2; int /*<<< orphan*/  CR1; } ;
struct TYPE_4__ {int /*<<< orphan*/ * EXTICR; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA2_Stream2_IRQn ; 
 int /*<<< orphan*/  DMA2_Stream3_IRQn ; 
 TYPE_3__* EXTI ; 
 int /*<<< orphan*/  EXTI4_IRQn ; 
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  MODE_INPUT ; 
 int /*<<< orphan*/  NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PULL_UP ; 
 TYPE_2__* SPI1 ; 
 int /*<<< orphan*/  SPI_CR1_SPE ; 
 int /*<<< orphan*/  SPI_CR2_RXNEIE ; 
 TYPE_1__* SYSCFG ; 
 int /*<<< orphan*/  SYSCFG_EXTICR2_EXTI4_PA ; 
 int /*<<< orphan*/  set_gpio_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gpio_pullup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void spi_init(void) {
  //puts("SPI init\n");
  SPI1->CR1 = SPI_CR1_SPE;

  // enable SPI interrupts
  //SPI1->CR2 = SPI_CR2_RXNEIE | SPI_CR2_ERRIE | SPI_CR2_TXEIE;
  SPI1->CR2 = SPI_CR2_RXNEIE;

  NVIC_EnableIRQ(DMA2_Stream2_IRQn);
  NVIC_EnableIRQ(DMA2_Stream3_IRQn);
  //NVIC_EnableIRQ(SPI1_IRQn);

  // reset handshake back to pull up
  set_gpio_mode(GPIOB, 0, MODE_INPUT);
  set_gpio_pullup(GPIOB, 0, PULL_UP);

  // setup interrupt on falling edge of SPI enable (on PA4)
  SYSCFG->EXTICR[2] = SYSCFG_EXTICR2_EXTI4_PA;
  EXTI->IMR |= (1U << 4);
  EXTI->FTSR |= (1U << 4);
  NVIC_EnableIRQ(EXTI4_IRQn);
}