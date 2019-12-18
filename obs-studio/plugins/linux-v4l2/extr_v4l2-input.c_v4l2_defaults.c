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
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int VIDEO_RANGE_DEFAULT ; 
 int /*<<< orphan*/  obs_data_set_default_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  obs_data_set_default_int (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void v4l2_defaults(obs_data_t *settings)
{
	obs_data_set_default_int(settings, "input", -1);
	obs_data_set_default_int(settings, "pixelformat", -1);
	obs_data_set_default_int(settings, "standard", -1);
	obs_data_set_default_int(settings, "dv_timing", -1);
	obs_data_set_default_int(settings, "resolution", -1);
	obs_data_set_default_int(settings, "framerate", -1);
	obs_data_set_default_int(settings, "color_range", VIDEO_RANGE_DEFAULT);
	obs_data_set_default_bool(settings, "buffering", true);
}