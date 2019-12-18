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
struct TYPE_4__ {unsigned int IMR; unsigned int RTSR; unsigned int FTSR; } ;
struct TYPE_3__ {int /*<<< orphan*/ * EXTICR; } ;

/* Variables and functions */
 TYPE_2__* EXTI ; 
 int /*<<< orphan*/  EXTI0_IRQn ; 
 int /*<<< orphan*/  EXTI1_IRQn ; 
 int /*<<< orphan*/  EXTI3_IRQn ; 
 scalar_t__ HARNESS_STATUS_FLIPPED ; 
 scalar_t__ HARNESS_STATUS_NORMAL ; 
 int /*<<< orphan*/  NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 TYPE_1__* SYSCFG ; 
 int /*<<< orphan*/  SYSCFG_EXTICR1_EXTI0_PC ; 
 int /*<<< orphan*/  SYSCFG_EXTICR1_EXTI3_PC ; 
 scalar_t__ car_harness_status ; 
 int /*<<< orphan*/  puts (char*) ; 

void harness_setup_ignition_interrupts(void){
  if(car_harness_status == HARNESS_STATUS_NORMAL){
    SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PC;
    EXTI->IMR |= (1U << 3);
    EXTI->RTSR |= (1U << 3);
    EXTI->FTSR |= (1U << 3);
    puts("setup interrupts: normal\n");
  } else if(car_harness_status == HARNESS_STATUS_FLIPPED) {
    SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PC;
    EXTI->IMR |= (1U << 0);
    EXTI->RTSR |= (1U << 0);
    EXTI->FTSR |= (1U << 0);
    NVIC_EnableIRQ(EXTI1_IRQn);
    puts("setup interrupts: flipped\n");
  } else {
    puts("tried to setup ignition interrupts without harness connected\n");
  }
  NVIC_EnableIRQ(EXTI0_IRQn);
  NVIC_EnableIRQ(EXTI3_IRQn);
}