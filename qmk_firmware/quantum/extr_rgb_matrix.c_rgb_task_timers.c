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
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ any_key_hit; } ;
struct TYPE_3__ {size_t count; scalar_t__* tick; } ;

/* Variables and functions */
 scalar_t__ UINT16_MAX ; 
 scalar_t__ UINT32_MAX ; 
 TYPE_2__ g_rgb_counters ; 
 TYPE_1__ last_hit_buffer ; 
 int /*<<< orphan*/  rgb_counters_buffer ; 
 scalar_t__ timer_elapsed32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read32 () ; 

__attribute__((used)) static void rgb_task_timers(void) {
    // Update double buffer timers
    uint16_t deltaTime  = timer_elapsed32(rgb_counters_buffer);
    rgb_counters_buffer = timer_read32();
    if (g_rgb_counters.any_key_hit < UINT32_MAX) {
        if (UINT32_MAX - deltaTime < g_rgb_counters.any_key_hit) {
            g_rgb_counters.any_key_hit = UINT32_MAX;
        } else {
            g_rgb_counters.any_key_hit += deltaTime;
        }
    }

    // Update double buffer last hit timers
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
    uint8_t count = last_hit_buffer.count;
    for (uint8_t i = 0; i < count; ++i) {
        if (UINT16_MAX - deltaTime < last_hit_buffer.tick[i]) {
            last_hit_buffer.count--;
            continue;
        }
        last_hit_buffer.tick[i] += deltaTime;
    }
#endif  // RGB_MATRIX_KEYREACTIVE_ENABLED
}