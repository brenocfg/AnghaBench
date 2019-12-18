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
 scalar_t__ HOOK_RATE_NORMAL ; 
 int /*<<< orphan*/  SETTING_ANTI_CHEAT_HOOK ; 
 int /*<<< orphan*/  SETTING_CAPTURE_OVERLAYS ; 
 int /*<<< orphan*/  SETTING_COMPATIBILITY ; 
 int /*<<< orphan*/  SETTING_CURSOR ; 
 int /*<<< orphan*/  SETTING_FORCE_SCALING ; 
 int /*<<< orphan*/  SETTING_HOOK_RATE ; 
 int /*<<< orphan*/  SETTING_LIMIT_FRAMERATE ; 
 int /*<<< orphan*/  SETTING_MODE ; 
 char* SETTING_MODE_ANY ; 
 int /*<<< orphan*/  SETTING_SCALE_RES ; 
 int /*<<< orphan*/  SETTING_TRANSPARENCY ; 
 int /*<<< orphan*/  SETTING_WINDOW_PRIORITY ; 
 scalar_t__ WINDOW_PRIORITY_EXE ; 
 int /*<<< orphan*/  obs_data_set_default_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_data_set_default_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_data_set_default_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void game_capture_defaults(obs_data_t *settings)
{
	obs_data_set_default_string(settings, SETTING_MODE, SETTING_MODE_ANY);
	obs_data_set_default_int(settings, SETTING_WINDOW_PRIORITY,
				 (int)WINDOW_PRIORITY_EXE);
	obs_data_set_default_bool(settings, SETTING_COMPATIBILITY, false);
	obs_data_set_default_bool(settings, SETTING_FORCE_SCALING, false);
	obs_data_set_default_bool(settings, SETTING_CURSOR, true);
	obs_data_set_default_bool(settings, SETTING_TRANSPARENCY, false);
	obs_data_set_default_string(settings, SETTING_SCALE_RES, "0x0");
	obs_data_set_default_bool(settings, SETTING_LIMIT_FRAMERATE, false);
	obs_data_set_default_bool(settings, SETTING_CAPTURE_OVERLAYS, false);
	obs_data_set_default_bool(settings, SETTING_ANTI_CHEAT_HOOK, true);
	obs_data_set_default_int(settings, SETTING_HOOK_RATE,
				 (int)HOOK_RATE_NORMAL);
}