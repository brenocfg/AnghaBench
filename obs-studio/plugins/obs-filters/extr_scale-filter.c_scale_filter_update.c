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
struct scale_filter_data {int valid; int base_canvas_resolution; int aspect_ratio_only; int /*<<< orphan*/  undistort; int /*<<< orphan*/  sampling; int /*<<< orphan*/  cy_in; int /*<<< orphan*/  cx_in; } ;
struct obs_video_info {int /*<<< orphan*/  base_height; int /*<<< orphan*/  base_width; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_SCALE_AREA ; 
 int /*<<< orphan*/  OBS_SCALE_BICUBIC ; 
 int /*<<< orphan*/  OBS_SCALE_BILINEAR ; 
 int /*<<< orphan*/  OBS_SCALE_LANCZOS ; 
 int /*<<< orphan*/  OBS_SCALE_POINT ; 
 int /*<<< orphan*/  S_RESOLUTION ; 
 int /*<<< orphan*/  S_SAMPLING ; 
 int /*<<< orphan*/  S_SAMPLING_AREA ; 
 int /*<<< orphan*/  S_SAMPLING_BILINEAR ; 
 int /*<<< orphan*/  S_SAMPLING_LANCZOS ; 
 int /*<<< orphan*/  S_SAMPLING_POINT ; 
 int /*<<< orphan*/  S_UNDISTORT ; 
 int /*<<< orphan*/  T_BASE ; 
 scalar_t__ astrcmpi (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_data_get_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_get_video_info (struct obs_video_info*) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scale_filter_update(void *data, obs_data_t *settings)
{
	struct scale_filter_data *filter = data;
	int ret;

	const char *res_str = obs_data_get_string(settings, S_RESOLUTION);
	const char *sampling = obs_data_get_string(settings, S_SAMPLING);

	filter->valid = true;
	filter->base_canvas_resolution = false;

	if (strcmp(res_str, T_BASE) == 0) {
		struct obs_video_info ovi;
		obs_get_video_info(&ovi);
		filter->aspect_ratio_only = false;
		filter->base_canvas_resolution = true;
		filter->cx_in = ovi.base_width;
		filter->cy_in = ovi.base_height;
	} else {
		ret = sscanf(res_str, "%dx%d", &filter->cx_in, &filter->cy_in);
		if (ret == 2) {
			filter->aspect_ratio_only = false;
		} else {
			ret = sscanf(res_str, "%d:%d", &filter->cx_in,
				     &filter->cy_in);
			if (ret != 2) {
				filter->valid = false;
				return;
			}

			filter->aspect_ratio_only = true;
		}
	}

	if (astrcmpi(sampling, S_SAMPLING_POINT) == 0) {
		filter->sampling = OBS_SCALE_POINT;

	} else if (astrcmpi(sampling, S_SAMPLING_BILINEAR) == 0) {
		filter->sampling = OBS_SCALE_BILINEAR;

	} else if (astrcmpi(sampling, S_SAMPLING_LANCZOS) == 0) {
		filter->sampling = OBS_SCALE_LANCZOS;

	} else if (astrcmpi(sampling, S_SAMPLING_AREA) == 0) {
		filter->sampling = OBS_SCALE_AREA;

	} else { /* S_SAMPLING_BICUBIC */
		filter->sampling = OBS_SCALE_BICUBIC;
	}

	filter->undistort = obs_data_get_bool(settings, S_UNDISTORT);
}