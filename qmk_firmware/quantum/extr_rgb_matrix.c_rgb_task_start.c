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
struct TYPE_4__ {int /*<<< orphan*/  tick; } ;
struct TYPE_3__ {scalar_t__ iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  RENDERING ; 
 int /*<<< orphan*/  g_last_hit_tracker ; 
 TYPE_2__ g_rgb_counters ; 
 int /*<<< orphan*/  last_hit_buffer ; 
 int /*<<< orphan*/  rgb_counters_buffer ; 
 TYPE_1__ rgb_effect_params ; 
 int /*<<< orphan*/  rgb_task_state ; 

__attribute__((used)) static void rgb_task_start(void) {
    // reset iter
    rgb_effect_params.iter = 0;

    // update double buffers
    g_rgb_counters.tick = rgb_counters_buffer;
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
    g_last_hit_tracker = last_hit_buffer;
#endif  // RGB_MATRIX_KEYREACTIVE_ENABLED

    // next task
    rgb_task_state = RENDERING;
}