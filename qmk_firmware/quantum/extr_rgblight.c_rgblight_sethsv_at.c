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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  enable; } ;
struct TYPE_4__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ LED_TYPE ;

/* Variables and functions */
 TYPE_3__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_setrgb_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sethsv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

void rgblight_sethsv_at(uint8_t hue, uint8_t sat, uint8_t val, uint8_t index) {
    if (!rgblight_config.enable) {
        return;
    }

    LED_TYPE tmp_led;
    sethsv(hue, sat, val, &tmp_led);
    rgblight_setrgb_at(tmp_led.r, tmp_led.g, tmp_led.b, index);
}