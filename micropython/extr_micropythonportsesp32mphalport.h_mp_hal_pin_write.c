#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mp_hal_pin_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_level (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void mp_hal_pin_write(mp_hal_pin_obj_t pin, int v) {
    gpio_set_level(pin, v);
}