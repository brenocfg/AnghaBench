#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int PSC; scalar_t__ SR; int /*<<< orphan*/  CR1; int /*<<< orphan*/  DIER; } ;
typedef  TYPE_1__ TIM_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  TIM_CR1_CEN ; 
 int /*<<< orphan*/  TIM_DIER_UIE ; 

void timer_init(TIM_TypeDef *TIM, int psc) {
  TIM->PSC = psc-1;
  TIM->DIER = TIM_DIER_UIE;
  TIM->CR1 = TIM_CR1_CEN;
  TIM->SR = 0;
}