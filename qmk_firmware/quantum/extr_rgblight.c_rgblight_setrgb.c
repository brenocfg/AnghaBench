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
typedef  size_t uint8_t ;
struct TYPE_4__ {size_t r; size_t g; size_t b; scalar_t__ w; } ;
struct TYPE_3__ {int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 size_t effect_end_pos ; 
 size_t effect_start_pos ; 
 TYPE_2__* led ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_set () ; 

void rgblight_setrgb(uint8_t r, uint8_t g, uint8_t b) {
    if (!rgblight_config.enable) {
        return;
    }

    for (uint8_t i = effect_start_pos; i < effect_end_pos; i++) {
        led[i].r = r;
        led[i].g = g;
        led[i].b = b;
#ifdef RGBW
        led[i].w = 0;
#endif
    }
    rgblight_set();
}