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
 int /*<<< orphan*/  SETTING_BRIGHTNESS ; 
 int /*<<< orphan*/  SETTING_COLOR_TYPE ; 
 int /*<<< orphan*/  SETTING_CONTRAST ; 
 int /*<<< orphan*/  SETTING_GAMMA ; 
 int /*<<< orphan*/  SETTING_KEY_COLOR ; 
 int /*<<< orphan*/  SETTING_OPACITY ; 
 int /*<<< orphan*/  SETTING_SIMILARITY ; 
 int /*<<< orphan*/  SETTING_SMOOTHNESS ; 
 int /*<<< orphan*/  obs_data_set_default_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  obs_data_set_default_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_data_set_default_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void color_key_defaults(obs_data_t *settings)
{
	obs_data_set_default_int(settings, SETTING_OPACITY, 100);
	obs_data_set_default_double(settings, SETTING_CONTRAST, 0.0);
	obs_data_set_default_double(settings, SETTING_BRIGHTNESS, 0.0);
	obs_data_set_default_double(settings, SETTING_GAMMA, 0.0);
	obs_data_set_default_int(settings, SETTING_KEY_COLOR, 0x00FF00);
	obs_data_set_default_string(settings, SETTING_COLOR_TYPE, "green");
	obs_data_set_default_int(settings, SETTING_SIMILARITY, 80);
	obs_data_set_default_int(settings, SETTING_SMOOTHNESS, 50);
}