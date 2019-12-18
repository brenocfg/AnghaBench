#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int pin; TYPE_3__* gpio; } ;
typedef  TYPE_1__ pin_obj_t ;
struct TYPE_5__ {int PDDR; } ;

/* Variables and functions */
 int GPIO_MODE_AF_OD ; 
 int GPIO_MODE_AF_PP ; 
 int GPIO_MODE_ANALOG ; 
 int GPIO_MODE_INPUT ; 
 int GPIO_MODE_OUTPUT_OD ; 
 int GPIO_MODE_OUTPUT_PP ; 
 int* GPIO_PIN_TO_PORT_PCR (TYPE_3__*,int) ; 
 int PORT_PCR_MUX_MASK ; 
 int PORT_PCR_ODE ; 

uint32_t pin_get_mode(const pin_obj_t *pin) {
    if (pin->gpio == NULL) {
        // Analog only pin
        return GPIO_MODE_ANALOG;
    }
    volatile uint32_t *port_pcr = GPIO_PIN_TO_PORT_PCR(pin->gpio, pin->pin);
    uint32_t pcr = *port_pcr;
    uint32_t af = (pcr & PORT_PCR_MUX_MASK) >> 8;
    if (af == 0) {
        return GPIO_MODE_ANALOG;
    }
    if (af == 1) {
        if (pin->gpio->PDDR & (1 << pin->pin)) {
            if (pcr & PORT_PCR_ODE) {
                return GPIO_MODE_OUTPUT_OD;
            }
            return GPIO_MODE_OUTPUT_PP;
        }
        return GPIO_MODE_INPUT;
    }

    if (pcr & PORT_PCR_ODE) {
        return GPIO_MODE_AF_OD;
    }
    return GPIO_MODE_AF_PP;
}