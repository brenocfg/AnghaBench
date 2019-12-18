#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  obs_data_t ;
struct TYPE_5__ {void* color_range; void* framerate; void* resolution; void* dv_timing; void* standard; void* pixfmt; void* input; scalar_t__ device_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_DATA (void*) ; 
 int /*<<< orphan*/  bfree (scalar_t__) ; 
 scalar_t__ bstrdup (int /*<<< orphan*/ ) ; 
 TYPE_1__* data ; 
 void* obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_init (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_terminate (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_update_source_flags (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void v4l2_update(void *vptr, obs_data_t *settings)
{
	V4L2_DATA(vptr);

	v4l2_terminate(data);

	if (data->device_id)
		bfree(data->device_id);

	data->device_id = bstrdup(obs_data_get_string(settings, "device_id"));
	data->input = obs_data_get_int(settings, "input");
	data->pixfmt = obs_data_get_int(settings, "pixelformat");
	data->standard = obs_data_get_int(settings, "standard");
	data->dv_timing = obs_data_get_int(settings, "dv_timing");
	data->resolution = obs_data_get_int(settings, "resolution");
	data->framerate = obs_data_get_int(settings, "framerate");
	data->color_range = obs_data_get_int(settings, "color_range");

	v4l2_update_source_flags(data, settings);

	v4l2_init(data);
}