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

/* Variables and functions */
 int /*<<< orphan*/  S_ATTACK_TIME ; 
 int /*<<< orphan*/  S_DETECTOR ; 
 int /*<<< orphan*/  S_OUTPUT_GAIN ; 
 int /*<<< orphan*/  S_PRESETS ; 
 int /*<<< orphan*/  S_RATIO ; 
 int /*<<< orphan*/  S_RELEASE_TIME ; 
 int /*<<< orphan*/  S_THRESHOLD ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_data_set_default_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  obs_data_set_default_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_data_set_default_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void expander_defaults(obs_data_t *s)
{
	const char *presets = obs_data_get_string(s, S_PRESETS);
	bool is_expander_preset = true;
	if (strcmp(presets, "gate") == 0)
		is_expander_preset = false;
	obs_data_set_default_string(s, S_PRESETS,
				    is_expander_preset ? "expander" : "gate");
	obs_data_set_default_double(s, S_RATIO,
				    is_expander_preset ? 2.0 : 10.0);
	obs_data_set_default_double(s, S_THRESHOLD, -40.0f);
	obs_data_set_default_int(s, S_ATTACK_TIME, 10);
	obs_data_set_default_int(s, S_RELEASE_TIME,
				 is_expander_preset ? 50 : 125);
	obs_data_set_default_double(s, S_OUTPUT_GAIN, 0.0);
	obs_data_set_default_string(s, S_DETECTOR, "RMS");
}