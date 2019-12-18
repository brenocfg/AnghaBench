#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  visualizer_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  default_suspend_animation ; 
 int /*<<< orphan*/  start_keyframe_animation (int /*<<< orphan*/ *) ; 

void user_visualizer_suspend(visualizer_state_t* state) {
    start_keyframe_animation(&default_suspend_animation);
}