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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int any_key_hit; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
#define  FLUSHING 131 
#define  RENDERING 130 
 int RGB_DISABLE_AFTER_TIMEOUT ; 
 scalar_t__ RGB_DISABLE_WHEN_USB_SUSPENDED ; 
#define  STARTING 129 
#define  SYNCING 128 
 TYPE_2__ g_rgb_counters ; 
 scalar_t__ g_suspend_state ; 
 TYPE_1__ rgb_matrix_config ; 
 int /*<<< orphan*/  rgb_matrix_indicators () ; 
 int /*<<< orphan*/  rgb_task_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgb_task_render (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgb_task_start () ; 
 int rgb_task_state ; 
 int /*<<< orphan*/  rgb_task_sync () ; 
 int /*<<< orphan*/  rgb_task_timers () ; 

void rgb_matrix_task(void) {
    rgb_task_timers();

    // Ideally we would also stop sending zeros to the LED driver PWM buffers
    // while suspended and just do a software shutdown. This is a cheap hack for now.
    bool    suspend_backlight = ((g_suspend_state && RGB_DISABLE_WHEN_USB_SUSPENDED) || (RGB_DISABLE_AFTER_TIMEOUT > 0 && g_rgb_counters.any_key_hit > RGB_DISABLE_AFTER_TIMEOUT * 60 * 20));
    uint8_t effect            = suspend_backlight || !rgb_matrix_config.enable ? 0 : rgb_matrix_config.mode;

    switch (rgb_task_state) {
        case STARTING:
            rgb_task_start();
            break;
        case RENDERING:
            rgb_task_render(effect);
            break;
        case FLUSHING:
            rgb_task_flush(effect);
            break;
        case SYNCING:
            rgb_task_sync();
            break;
    }

    if (!suspend_backlight) {
        rgb_matrix_indicators();
    }
}