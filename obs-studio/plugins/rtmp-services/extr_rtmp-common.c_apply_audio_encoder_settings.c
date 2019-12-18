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
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 scalar_t__ json_integer_value (int /*<<< orphan*/ *) ; 
 scalar_t__ json_is_integer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char*) ; 
 int obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_set_int (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void apply_audio_encoder_settings(obs_data_t *settings,
					 json_t *recommended)
{
	json_t *item = json_object_get(recommended, "max audio bitrate");
	if (json_is_integer(item)) {
		int max_bitrate = (int)json_integer_value(item);
		if (obs_data_get_int(settings, "bitrate") > max_bitrate)
			obs_data_set_int(settings, "bitrate", max_bitrate);
	}
}