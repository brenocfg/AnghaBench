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

/* Variables and functions */
 int /*<<< orphan*/  OBS_COMBO_FORMAT_STRING ; 
 int /*<<< orphan*/  OBS_COMBO_TYPE_LIST ; 
 char* TEXT_ACCURACY ; 
 char* TEXT_ASYNC_DEPTH ; 
 char* TEXT_BFRAMES ; 
 char* TEXT_CONVERGENCE ; 
 char* TEXT_ICQ_QUALITY ; 
 char* TEXT_KEYINT_SEC ; 
 char* TEXT_LA_DEPTH ; 
 char* TEXT_MAX_BITRATE ; 
 int /*<<< orphan*/  TEXT_MBBRC ; 
 int /*<<< orphan*/  TEXT_PROFILE ; 
 int /*<<< orphan*/  TEXT_RATE_CONTROL ; 
 int /*<<< orphan*/  TEXT_SPEED ; 
 char* TEXT_TARGET_BITRATE ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  add_rate_controls (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_strings (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_skl_or_greater_platform () ; 
 int /*<<< orphan*/  obs_properties_add_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_add_int (int /*<<< orphan*/ *,char*,char*,int,int,int) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_int_set_suffix (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_property_set_modified_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsv_profile_names ; 
 int /*<<< orphan*/  qsv_ratecontrols ; 
 int /*<<< orphan*/  qsv_usage_names ; 
 int /*<<< orphan*/  rate_control_modified ; 

__attribute__((used)) static obs_properties_t *obs_qsv_props(void *unused)
{
	UNUSED_PARAMETER(unused);

	obs_properties_t *props = obs_properties_create();
	obs_property_t *list;

	list = obs_properties_add_list(props, "target_usage", TEXT_SPEED,
				       OBS_COMBO_TYPE_LIST,
				       OBS_COMBO_FORMAT_STRING);
	add_strings(list, qsv_usage_names);

	list = obs_properties_add_list(props, "profile", TEXT_PROFILE,
				       OBS_COMBO_TYPE_LIST,
				       OBS_COMBO_FORMAT_STRING);
	add_strings(list, qsv_profile_names);

	obs_properties_add_int(props, "keyint_sec", TEXT_KEYINT_SEC, 1, 20, 1);
	obs_properties_add_int(props, "async_depth", TEXT_ASYNC_DEPTH, 1, 7, 1);

	list = obs_properties_add_list(props, "rate_control", TEXT_RATE_CONTROL,
				       OBS_COMBO_TYPE_LIST,
				       OBS_COMBO_FORMAT_STRING);
	add_rate_controls(list, qsv_ratecontrols);
	obs_property_set_modified_callback(list, rate_control_modified);

	obs_property_t *p;
	p = obs_properties_add_int(props, "bitrate", TEXT_TARGET_BITRATE, 50,
				   10000000, 50);
	obs_property_int_set_suffix(p, " Kbps");

	p = obs_properties_add_int(props, "max_bitrate", TEXT_MAX_BITRATE, 50,
				   10000000, 50);
	obs_property_int_set_suffix(p, " Kbps");

	obs_properties_add_int(props, "accuracy", TEXT_ACCURACY, 0, 10000, 1);
	obs_properties_add_int(props, "convergence", TEXT_CONVERGENCE, 0, 10,
			       1);
	obs_properties_add_int(props, "qpi", "QPI", 1, 51, 1);
	obs_properties_add_int(props, "qpp", "QPP", 1, 51, 1);
	obs_properties_add_int(props, "qpb", "QPB", 1, 51, 1);
	obs_properties_add_int(props, "icq_quality", TEXT_ICQ_QUALITY, 1, 51,
			       1);
	obs_properties_add_int(props, "la_depth", TEXT_LA_DEPTH, 10, 100, 1);
	obs_properties_add_int(props, "bframes", TEXT_BFRAMES, 0, 3, 1);

	if (is_skl_or_greater_platform())
		obs_properties_add_bool(props, "mbbrc", TEXT_MBBRC);

	return props;
}