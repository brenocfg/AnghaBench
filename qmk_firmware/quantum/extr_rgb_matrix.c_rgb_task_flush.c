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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYNCING ; 
 int /*<<< orphan*/  rgb_last_effect ; 
 int /*<<< orphan*/  rgb_last_enable ; 
 TYPE_1__ rgb_matrix_config ; 
 int /*<<< orphan*/  rgb_matrix_update_pwm_buffers () ; 
 int /*<<< orphan*/  rgb_task_state ; 

__attribute__((used)) static void rgb_task_flush(uint8_t effect) {
    // update last trackers after the first full render so we can init over several frames
    rgb_last_effect = effect;
    rgb_last_enable = rgb_matrix_config.enable;

    // update pwm buffers
    rgb_matrix_update_pwm_buffers();

    // next task
    rgb_task_state = SYNCING;
}