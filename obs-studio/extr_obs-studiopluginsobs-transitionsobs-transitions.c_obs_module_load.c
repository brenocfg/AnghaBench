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

/* Variables and functions */
 int /*<<< orphan*/  cut_transition ; 
 int /*<<< orphan*/  fade_to_color_transition ; 
 int /*<<< orphan*/  fade_transition ; 
 int /*<<< orphan*/  luma_wipe_transition ; 
 int /*<<< orphan*/  obs_register_source (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slide_transition ; 
 int /*<<< orphan*/  stinger_transition ; 
 int /*<<< orphan*/  swipe_transition ; 

bool obs_module_load(void)
{
	obs_register_source(&cut_transition);
	obs_register_source(&fade_transition);
	obs_register_source(&swipe_transition);
	obs_register_source(&slide_transition);
	obs_register_source(&stinger_transition);
	obs_register_source(&fade_to_color_transition);
	obs_register_source(&luma_wipe_transition);
	return true;
}