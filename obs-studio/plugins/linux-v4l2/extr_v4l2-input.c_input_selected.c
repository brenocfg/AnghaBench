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
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  obs_properties_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * obs_properties_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_property_modified (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_close (int) ; 
 int /*<<< orphan*/  v4l2_format_list (int,int /*<<< orphan*/ *) ; 
 int v4l2_open (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool input_selected(obs_properties_t *props, obs_property_t *p,
			   obs_data_t *settings)
{
	UNUSED_PARAMETER(p);
	int dev = v4l2_open(obs_data_get_string(settings, "device_id"),
			    O_RDWR | O_NONBLOCK);
	if (dev == -1)
		return false;

	obs_property_t *prop = obs_properties_get(props, "pixelformat");
	v4l2_format_list(dev, prop);
	v4l2_close(dev);

	obs_property_modified(prop, settings);

	return true;
}