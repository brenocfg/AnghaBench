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
struct TYPE_4__ {int need_update; int first_update_of_frame; int last_update_of_frame; scalar_t__ time_left_in_frame; int /*<<< orphan*/  num_frames; int /*<<< orphan*/  current_frame; } ;
typedef  TYPE_1__ keyframe_animation_t ;

/* Variables and functions */
 int MAX_SIMULTANEOUS_ANIMATIONS ; 
 TYPE_1__** animations ; 

void stop_keyframe_animation(keyframe_animation_t* animation) {
    animation->current_frame         = animation->num_frames;
    animation->time_left_in_frame    = 0;
    animation->need_update           = true;
    animation->first_update_of_frame = false;
    animation->last_update_of_frame  = false;
    for (int i = 0; i < MAX_SIMULTANEOUS_ANIMATIONS; i++) {
        if (animations[i] == animation) {
            animations[i] = NULL;
            return;
        }
    }
}