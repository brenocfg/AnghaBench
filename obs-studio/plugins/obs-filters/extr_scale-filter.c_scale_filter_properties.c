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
typedef  int /*<<< orphan*/  uint32_t ;
struct obs_video_info {int base_width; int base_height; } ;
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  obs_properties_t ;

/* Variables and functions */
 size_t NUM_ASPECTS ; 
 int NUM_DOWNSCALES ; 
 int /*<<< orphan*/  OBS_COMBO_FORMAT_STRING ; 
 int /*<<< orphan*/  OBS_COMBO_TYPE_EDITABLE ; 
 int /*<<< orphan*/  OBS_COMBO_TYPE_LIST ; 
 int /*<<< orphan*/  S_RESOLUTION ; 
 int /*<<< orphan*/  S_SAMPLING ; 
 char* S_SAMPLING_AREA ; 
 char* S_SAMPLING_BICUBIC ; 
 char* S_SAMPLING_BILINEAR ; 
 char* S_SAMPLING_LANCZOS ; 
 char* S_SAMPLING_POINT ; 
 int /*<<< orphan*/  S_UNDISTORT ; 
 char* T_BASE ; 
 char* T_NONE ; 
 int /*<<< orphan*/  T_RESOLUTION ; 
 int /*<<< orphan*/  T_SAMPLING ; 
 char* T_SAMPLING_AREA ; 
 char* T_SAMPLING_BICUBIC ; 
 char* T_SAMPLING_BILINEAR ; 
 char* T_SAMPLING_LANCZOS ; 
 char* T_SAMPLING_POINT ; 
 int /*<<< orphan*/  T_UNDISTORT ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 char** aspects ; 
 double* downscale_vals ; 
 int /*<<< orphan*/  obs_get_video_info (struct obs_video_info*) ; 
 int /*<<< orphan*/  obs_properties_add_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_list_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  obs_property_set_modified_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sampling_modified ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 

__attribute__((used)) static obs_properties_t *scale_filter_properties(void *data)
{
	obs_properties_t *props = obs_properties_create();
	struct obs_video_info ovi;
	obs_property_t *p;
	uint32_t cx;
	uint32_t cy;

	struct {
		int cx;
		int cy;
	} downscales[NUM_DOWNSCALES];

	/* ----------------- */

	obs_get_video_info(&ovi);
	cx = ovi.base_width;
	cy = ovi.base_height;

	for (size_t i = 0; i < NUM_DOWNSCALES; i++) {
		downscales[i].cx = (int)((double)cx / downscale_vals[i]);
		downscales[i].cy = (int)((double)cy / downscale_vals[i]);
	}

	p = obs_properties_add_list(props, S_SAMPLING, T_SAMPLING,
				    OBS_COMBO_TYPE_LIST,
				    OBS_COMBO_FORMAT_STRING);
	obs_property_set_modified_callback(p, sampling_modified);
	obs_property_list_add_string(p, T_SAMPLING_POINT, S_SAMPLING_POINT);
	obs_property_list_add_string(p, T_SAMPLING_BILINEAR,
				     S_SAMPLING_BILINEAR);
	obs_property_list_add_string(p, T_SAMPLING_BICUBIC, S_SAMPLING_BICUBIC);
	obs_property_list_add_string(p, T_SAMPLING_LANCZOS, S_SAMPLING_LANCZOS);
	obs_property_list_add_string(p, T_SAMPLING_AREA, S_SAMPLING_AREA);

	/* ----------------- */

	p = obs_properties_add_list(props, S_RESOLUTION, T_RESOLUTION,
				    OBS_COMBO_TYPE_EDITABLE,
				    OBS_COMBO_FORMAT_STRING);

	obs_property_list_add_string(p, T_NONE, T_NONE);
	obs_property_list_add_string(p, T_BASE, T_BASE);

	for (size_t i = 0; i < NUM_ASPECTS; i++)
		obs_property_list_add_string(p, aspects[i], aspects[i]);

	for (size_t i = 0; i < NUM_DOWNSCALES; i++) {
		char str[32];
		snprintf(str, 32, "%dx%d", downscales[i].cx, downscales[i].cy);
		obs_property_list_add_string(p, str, str);
	}

	obs_properties_add_bool(props, S_UNDISTORT, T_UNDISTORT);

	/* ----------------- */

	UNUSED_PARAMETER(data);
	return props;
}