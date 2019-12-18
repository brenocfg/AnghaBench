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
 int /*<<< orphan*/  TEXT_BFRAMES ; 
 int /*<<< orphan*/  TEXT_BITRATE ; 
 int /*<<< orphan*/  TEXT_KEYINT_SEC ; 
 int /*<<< orphan*/  TEXT_MAX_BITRATE ; 
 int /*<<< orphan*/  TEXT_MAX_BITRATE_WINDOW ; 
 char* TEXT_NONE ; 
 int /*<<< orphan*/  TEXT_PROFILE ; 
 int /*<<< orphan*/  TEXT_USE_MAX_BITRATE ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  limit_bitrate_modified ; 
 int /*<<< orphan*/ * obs_properties_add_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_properties_add_float (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,float,float,float) ; 
 int /*<<< orphan*/ * obs_properties_add_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_int_set_suffix (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_property_list_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  obs_property_set_modified_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static obs_properties_t *vt_h264_properties(void *unused)
{
	UNUSED_PARAMETER(unused);

	obs_properties_t *props = obs_properties_create();
	obs_property_t *p;

	p = obs_properties_add_int(props, "bitrate", TEXT_BITRATE, 50, 10000000,
				   50);
	obs_property_int_set_suffix(p, " Kbps");

	p = obs_properties_add_bool(props, "limit_bitrate",
				    TEXT_USE_MAX_BITRATE);
	obs_property_set_modified_callback(p, limit_bitrate_modified);

	p = obs_properties_add_int(props, "max_bitrate", TEXT_MAX_BITRATE, 50,
				   10000000, 50);
	obs_property_int_set_suffix(p, " Kbps");

	obs_properties_add_float(props, "max_bitrate_window",
				 TEXT_MAX_BITRATE_WINDOW, 0.10f, 10.0f, 0.25f);

	obs_properties_add_int(props, "keyint_sec", TEXT_KEYINT_SEC, 0, 20, 1);

	p = obs_properties_add_list(props, "profile", TEXT_PROFILE,
				    OBS_COMBO_TYPE_LIST,
				    OBS_COMBO_FORMAT_STRING);
	obs_property_list_add_string(p, TEXT_NONE, "");
	obs_property_list_add_string(p, "baseline", "baseline");
	obs_property_list_add_string(p, "main", "main");
	obs_property_list_add_string(p, "high", "high");

	obs_properties_add_bool(props, "bframes", TEXT_BFRAMES);

	return props;
}