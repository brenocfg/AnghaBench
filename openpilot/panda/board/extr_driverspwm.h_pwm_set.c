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
typedef  unsigned int uint16_t ;
struct TYPE_3__ {unsigned int CCR1; unsigned int CCR2; unsigned int CCR3; unsigned int CCR4; } ;
typedef  TYPE_1__ TIM_TypeDef ;

/* Variables and functions */
 unsigned int PWM_COUNTER_OVERFLOW ; 

void pwm_set(TIM_TypeDef *TIM, uint8_t channel, uint8_t percentage){
    uint16_t comp_value = (((uint16_t) percentage * PWM_COUNTER_OVERFLOW) / 100U);
    switch(channel){
        case 1U:
            TIM->CCR1 = comp_value;
            break;
        case 2U:
            TIM->CCR2 = comp_value;
            break;
        case 3U:
            TIM->CCR3 = comp_value;
            break;
        case 4U:
            TIM->CCR4 = comp_value;
            break;
        default:
            break;
    }
}