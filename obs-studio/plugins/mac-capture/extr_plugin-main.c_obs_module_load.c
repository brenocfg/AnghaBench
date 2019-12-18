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
 int /*<<< orphan*/  coreaudio_input_capture_info ; 
 int /*<<< orphan*/  coreaudio_output_capture_info ; 
 int /*<<< orphan*/  display_capture_info ; 
 int /*<<< orphan*/  obs_register_source (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  window_capture_info ; 

bool obs_module_load(void)
{
	obs_register_source(&coreaudio_input_capture_info);
	obs_register_source(&coreaudio_output_capture_info);
	obs_register_source(&display_capture_info);
	obs_register_source(&window_capture_info);
	return true;
}