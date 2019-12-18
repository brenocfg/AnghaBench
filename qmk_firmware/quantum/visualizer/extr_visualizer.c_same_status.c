#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ layer; scalar_t__ default_layer; scalar_t__ mods; scalar_t__ leds; scalar_t__ suspended; scalar_t__ backlight_level; int /*<<< orphan*/  user_data; } ;
typedef  TYPE_1__ visualizer_keyboard_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  VISUALIZER_USER_DATA_SIZE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool same_status(visualizer_keyboard_status_t* status1, visualizer_keyboard_status_t* status2) {
    return status1->layer == status2->layer && status1->default_layer == status2->default_layer && status1->mods == status2->mods && status1->leds == status2->leds && status1->suspended == status2->suspended
#ifdef BACKLIGHT_ENABLE
           && status1->backlight_level == status2->backlight_level
#endif
#ifdef VISUALIZER_USER_DATA_SIZE
           && memcmp(status1->user_data, status2->user_data, VISUALIZER_USER_DATA_SIZE) == 0
#endif
        ;
}