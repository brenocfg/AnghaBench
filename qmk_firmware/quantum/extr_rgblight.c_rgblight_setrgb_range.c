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
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {scalar_t__ w; scalar_t__ b; scalar_t__ g; scalar_t__ r; } ;
struct TYPE_3__ {int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 scalar_t__ RGBLED_NUM ; 
 TYPE_2__* led ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_set () ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void rgblight_setrgb_range(uint8_t r, uint8_t g, uint8_t b, uint8_t start, uint8_t end) {
    if (!rgblight_config.enable || start < 0 || start >= end || end > RGBLED_NUM) {
        return;
    }

    for (uint8_t i = start; i < end; i++) {
        led[i].r = r;
        led[i].g = g;
        led[i].b = b;
#ifdef RGBW
        led[i].w = 0;
#endif
    }
    rgblight_set();
    wait_ms(1);
}