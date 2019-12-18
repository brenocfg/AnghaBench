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
struct color_key_filter_data {float similarity; float smoothness; int /*<<< orphan*/  key_color; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SETTING_COLOR_TYPE ; 
 int /*<<< orphan*/  SETTING_KEY_COLOR ; 
 int /*<<< orphan*/  SETTING_SIMILARITY ; 
 int /*<<< orphan*/  SETTING_SMOOTHNESS ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  vec4_from_rgba (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void key_settings_update(struct color_key_filter_data *filter,
				       obs_data_t *settings)
{
	int64_t similarity = obs_data_get_int(settings, SETTING_SIMILARITY);
	int64_t smoothness = obs_data_get_int(settings, SETTING_SMOOTHNESS);
	uint32_t key_color =
		(uint32_t)obs_data_get_int(settings, SETTING_KEY_COLOR);
	const char *key_type =
		obs_data_get_string(settings, SETTING_COLOR_TYPE);

	if (strcmp(key_type, "green") == 0)
		key_color = 0x00FF00;
	else if (strcmp(key_type, "blue") == 0)
		key_color = 0xFF0000;
	else if (strcmp(key_type, "red") == 0)
		key_color = 0x0000FF;
	else if (strcmp(key_type, "magenta") == 0)
		key_color = 0xFF00FF;

	vec4_from_rgba(&filter->key_color, key_color | 0xFF000000);

	filter->similarity = (float)similarity / 1000.0f;
	filter->smoothness = (float)smoothness / 1000.0f;
}