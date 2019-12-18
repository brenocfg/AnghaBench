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
typedef  int uint8_t ;
struct TYPE_3__ {int* frame_lengths; size_t current_frame; int time_left_in_frame; } ;
typedef  TYPE_1__ keyframe_animation_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t fade_led_color(keyframe_animation_t* animation, int from, int to) {
    int frame_length = animation->frame_lengths[animation->current_frame];
    int current_pos  = frame_length - animation->time_left_in_frame;
    int delta        = to - from;
    int luma         = (delta * current_pos) / frame_length;
    luma += from;
    return luma;
}