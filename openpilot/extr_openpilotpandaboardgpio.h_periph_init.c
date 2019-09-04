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
struct TYPE_2__ {int /*<<< orphan*/  APB2ENR; int /*<<< orphan*/  AHB2ENR; int /*<<< orphan*/  APB1ENR; int /*<<< orphan*/  AHB1ENR; } ;

/* Variables and functions */
 TYPE_1__* RCC ; 
 int /*<<< orphan*/  RCC_AHB1ENR_DMA2EN ; 
 int /*<<< orphan*/  RCC_AHB1ENR_GPIOAEN ; 
 int /*<<< orphan*/  RCC_AHB1ENR_GPIOBEN ; 
 int /*<<< orphan*/  RCC_AHB1ENR_GPIOCEN ; 
 int /*<<< orphan*/  RCC_AHB1ENR_GPIODEN ; 
 int /*<<< orphan*/  RCC_AHB2ENR_OTGFSEN ; 
 int /*<<< orphan*/  RCC_APB1ENR_CAN1EN ; 
 int /*<<< orphan*/  RCC_APB1ENR_CAN2EN ; 
 int /*<<< orphan*/  RCC_APB1ENR_DACEN ; 
 int /*<<< orphan*/  RCC_APB1ENR_TIM2EN ; 
 int /*<<< orphan*/  RCC_APB1ENR_TIM3EN ; 
 int /*<<< orphan*/  RCC_APB1ENR_TIM4EN ; 
 int /*<<< orphan*/  RCC_APB1ENR_TIM5EN ; 
 int /*<<< orphan*/  RCC_APB1ENR_TIM6EN ; 
 int /*<<< orphan*/  RCC_APB1ENR_USART2EN ; 
 int /*<<< orphan*/  RCC_APB1ENR_USART3EN ; 
 int /*<<< orphan*/  RCC_APB2ENR_ADC1EN ; 
 int /*<<< orphan*/  RCC_APB2ENR_SPI1EN ; 
 int /*<<< orphan*/  RCC_APB2ENR_SYSCFGEN ; 
 int /*<<< orphan*/  RCC_APB2ENR_TIM1EN ; 
 int /*<<< orphan*/  RCC_APB2ENR_USART1EN ; 

void periph_init() {
  // enable GPIOB, UART2, CAN, USB clock
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

  RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
  RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
  #ifdef PANDA
    RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
  #endif
  RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
  RCC->APB1ENR |= RCC_APB1ENR_CAN2EN;
  #ifdef CAN3
    RCC->APB1ENR |= RCC_APB1ENR_CAN3EN;
  #endif
  RCC->APB1ENR |= RCC_APB1ENR_DACEN;
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
  RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
  RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN;
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

  // needed?
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}