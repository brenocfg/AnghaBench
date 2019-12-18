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
struct dstr {char const* array; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  obs_data_item_t ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 scalar_t__ OBS_DATA_STRING ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_is_empty (struct dstr*) ; 
 scalar_t__ json_integer_value (int /*<<< orphan*/ *) ; 
 scalar_t__ json_is_integer (int /*<<< orphan*/ *) ; 
 scalar_t__ json_is_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char*) ; 
 char* json_string_value (int /*<<< orphan*/ *) ; 
 int obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * obs_data_item_byname (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_item_gettype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_set_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  obs_data_set_string (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static void apply_video_encoder_settings(obs_data_t *settings,
					 json_t *recommended)
{
	json_t *item = json_object_get(recommended, "keyint");
	if (json_is_integer(item)) {
		int keyint = (int)json_integer_value(item);
		obs_data_set_int(settings, "keyint_sec", keyint);
	}

	obs_data_set_string(settings, "rate_control", "CBR");

	item = json_object_get(recommended, "profile");
	obs_data_item_t *enc_item = obs_data_item_byname(settings, "profile");
	if (json_is_string(item) &&
	    obs_data_item_gettype(enc_item) == OBS_DATA_STRING) {
		const char *profile = json_string_value(item);
		obs_data_set_string(settings, "profile", profile);
	}

	item = json_object_get(recommended, "max video bitrate");
	if (json_is_integer(item)) {
		int max_bitrate = (int)json_integer_value(item);
		if (obs_data_get_int(settings, "bitrate") > max_bitrate) {
			obs_data_set_int(settings, "bitrate", max_bitrate);
			obs_data_set_int(settings, "buffer_size", max_bitrate);
		}
	}

	item = json_object_get(recommended, "bframes");
	if (json_is_integer(item))
		obs_data_set_int(settings, "bf", 0);

	item = json_object_get(recommended, "x264opts");
	if (json_is_string(item)) {
		const char *x264_settings = json_string_value(item);
		const char *cur_settings =
			obs_data_get_string(settings, "x264opts");
		struct dstr opts;

		dstr_init_copy(&opts, cur_settings);
		if (!dstr_is_empty(&opts))
			dstr_cat(&opts, " ");
		dstr_cat(&opts, x264_settings);

		obs_data_set_string(settings, "x264opts", opts.array);
		dstr_free(&opts);
	}
}