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
typedef  int uint8_t ;
struct TYPE_3__ {int CR1; int CCMR1; int CCMR2; int /*<<< orphan*/  EGR; int /*<<< orphan*/  ARR; int /*<<< orphan*/  CCER; } ;
typedef  TYPE_1__ TIM_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  PWM_COUNTER_OVERFLOW ; 
 int /*<<< orphan*/  TIM_CCER_CC1E ; 
 int /*<<< orphan*/  TIM_CCER_CC2E ; 
 int /*<<< orphan*/  TIM_CCER_CC3E ; 
 int /*<<< orphan*/  TIM_CCER_CC4E ; 
 int TIM_CCMR1_OC1M_1 ; 
 int TIM_CCMR1_OC1M_2 ; 
 int TIM_CCMR1_OC1PE ; 
 int TIM_CCMR1_OC2M_1 ; 
 int TIM_CCMR1_OC2M_2 ; 
 int TIM_CCMR1_OC2PE ; 
 int TIM_CCMR2_OC3M_1 ; 
 int TIM_CCMR2_OC3M_2 ; 
 int TIM_CCMR2_OC3PE ; 
 int TIM_CCMR2_OC4M_1 ; 
 int TIM_CCMR2_OC4M_2 ; 
 int TIM_CCMR2_OC4PE ; 
 int TIM_CR1_ARPE ; 
 int TIM_CR1_CEN ; 
 int /*<<< orphan*/  TIM_EGR_UG ; 

void pwm_init(TIM_TypeDef *TIM, uint8_t channel){
    // Enable timer and auto-reload
    TIM->CR1 = TIM_CR1_CEN | TIM_CR1_ARPE;

    // Set channel as PWM mode 1 and enable output
    switch(channel){
        case 1U:
            TIM->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE);
            TIM->CCER |= TIM_CCER_CC1E;
            break;
        case 2U:
            TIM->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE);
            TIM->CCER |= TIM_CCER_CC2E;
            break;
        case 3U:
            TIM->CCMR2 |= (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE);
            TIM->CCER |= TIM_CCER_CC3E;
            break;
        case 4U:
            TIM->CCMR2 |= (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4PE);
            TIM->CCER |= TIM_CCER_CC4E;
            break;
        default:
            break;
    }

    // Set max counter value
    TIM->ARR = PWM_COUNTER_OVERFLOW;

    // Update registers and clear counter
    TIM->EGR |= TIM_EGR_UG;
}