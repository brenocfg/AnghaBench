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
typedef  int /*<<< orphan*/  visualizer_state_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {float* frame_lengths; size_t current_frame; float time_left_in_frame; } ;
typedef  TYPE_1__ keyframe_animation_t ;

/* Variables and functions */
 int /*<<< orphan*/  LED_DISPLAY ; 
 int /*<<< orphan*/  LUMA2COLOR (int /*<<< orphan*/ ) ; 
 int NUM_COLS ; 
 scalar_t__ NUM_ROWS ; 
 int /*<<< orphan*/  gdispGDrawLine (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  off_on_gradient (float,int,int) ; 

bool led_backlight_keyframe_half_period_sweep_to_on(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    float frame_length = animation->frame_lengths[animation->current_frame];
    float current_pos = frame_length - animation->time_left_in_frame;
    float t = current_pos / frame_length;
    for (int i=0; i< NUM_COLS; i++) {
        uint8_t color = off_on_gradient(t*2, i, NUM_COLS);
        gdispGDrawLine(LED_DISPLAY, i, 0, i, NUM_ROWS - 1, LUMA2COLOR(color));
    }
    return true;
}