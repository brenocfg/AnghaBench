#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tick; } ;

/* Variables and functions */
 scalar_t__ RGB_MATRIX_LED_FLUSH_LIMIT ; 
 int /*<<< orphan*/  STARTING ; 
 TYPE_1__ g_rgb_counters ; 
 int /*<<< orphan*/  rgb_task_state ; 
 scalar_t__ timer_elapsed32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rgb_task_sync(void) {
    // next task
    if (timer_elapsed32(g_rgb_counters.tick) >= RGB_MATRIX_LED_FLUSH_LIMIT) rgb_task_state = STARTING;
}