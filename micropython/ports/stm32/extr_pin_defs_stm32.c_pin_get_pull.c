#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int pin; TYPE_1__* gpio; } ;
typedef  TYPE_2__ pin_obj_t ;
struct TYPE_4__ {int PUPDR; } ;

/* Variables and functions */

uint32_t pin_get_pull(const pin_obj_t *pin) {
    return (pin->gpio->PUPDR >> (pin->pin * 2)) & 3;
}