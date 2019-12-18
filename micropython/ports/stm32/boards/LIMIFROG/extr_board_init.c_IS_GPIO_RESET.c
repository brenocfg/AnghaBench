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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int IDR; } ;
typedef  TYPE_1__ GPIO_TypeDef ;
typedef  scalar_t__ GPIO_PinState ;

/* Variables and functions */
 scalar_t__ GPIO_PIN_RESET ; 
 scalar_t__ GPIO_PIN_SET ; 

__attribute__((used)) static inline int  IS_GPIO_RESET(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_PinState bitstatus;
      if((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
            {
                    bitstatus = GPIO_PIN_SET;
                      }
        else
              {
                      bitstatus = GPIO_PIN_RESET;
                        }
          return (bitstatus==GPIO_PIN_RESET);
}