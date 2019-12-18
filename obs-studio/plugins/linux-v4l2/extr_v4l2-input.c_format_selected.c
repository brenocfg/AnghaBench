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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  obs_properties_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int V4L2_IN_CAP_DV_TIMINGS ; 
 int V4L2_IN_CAP_STD ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * obs_properties_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_property_modified (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_property_set_visible (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  v4l2_close (int) ; 
 int /*<<< orphan*/  v4l2_dv_timing_list (int,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_get_input_caps (int,int,int*) ; 
 int v4l2_open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_resolution_list (int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_standard_list (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool format_selected(obs_properties_t *props, obs_property_t *p,
			    obs_data_t *settings)
{
	UNUSED_PARAMETER(p);
	int dev = v4l2_open(obs_data_get_string(settings, "device_id"),
			    O_RDWR | O_NONBLOCK);
	if (dev == -1)
		return false;

	int input = (int)obs_data_get_int(settings, "input");
	uint32_t caps = 0;
	if (v4l2_get_input_caps(dev, input, &caps) < 0)
		return false;
	caps &= V4L2_IN_CAP_STD | V4L2_IN_CAP_DV_TIMINGS;

	obs_property_t *resolution = obs_properties_get(props, "resolution");
	obs_property_t *framerate = obs_properties_get(props, "framerate");
	obs_property_t *standard = obs_properties_get(props, "standard");
	obs_property_t *dv_timing = obs_properties_get(props, "dv_timing");

	obs_property_set_visible(resolution, (!caps) ? true : false);
	obs_property_set_visible(framerate, (!caps) ? true : false);
	obs_property_set_visible(standard,
				 (caps & V4L2_IN_CAP_STD) ? true : false);
	obs_property_set_visible(
		dv_timing, (caps & V4L2_IN_CAP_DV_TIMINGS) ? true : false);

	if (!caps) {
		v4l2_resolution_list(dev,
				     obs_data_get_int(settings, "pixelformat"),
				     resolution);
	}
	if (caps & V4L2_IN_CAP_STD)
		v4l2_standard_list(dev, standard);
	if (caps & V4L2_IN_CAP_DV_TIMINGS)
		v4l2_dv_timing_list(dev, dv_timing);

	v4l2_close(dev);

	if (!caps)
		obs_property_modified(resolution, settings);
	if (caps & V4L2_IN_CAP_STD)
		obs_property_modified(standard, settings);
	if (caps & V4L2_IN_CAP_DV_TIMINGS)
		obs_property_modified(dv_timing, settings);

	return true;
}