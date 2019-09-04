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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  idx; } ;
typedef  TYPE_1__ pin_af_obj_t ;
typedef  int /*<<< orphan*/  mp_hal_pin_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_hal_pin_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* pin_find_af (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool mp_hal_pin_config_alt(mp_hal_pin_obj_t pin, uint32_t mode, uint32_t pull, uint8_t fn, uint8_t unit) {
    const pin_af_obj_t *af = pin_find_af(pin, fn, unit);
    if (af == NULL) {
        return false;
    }
    mp_hal_pin_config(pin, mode, pull, af->idx);
    return true;
}