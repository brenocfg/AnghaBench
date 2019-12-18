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
 int /*<<< orphan*/  S_BEHAVIOR ; 
 char* S_BEHAVIOR_ALWAYS_PLAY ; 
 int /*<<< orphan*/  S_CUSTOM_SIZE ; 
 int /*<<< orphan*/  S_LOOP ; 
 int /*<<< orphan*/  S_MODE ; 
 char* S_MODE_AUTO ; 
 int /*<<< orphan*/  S_SLIDE_TIME ; 
 int /*<<< orphan*/  S_TRANSITION ; 
 int /*<<< orphan*/  S_TR_SPEED ; 
 char* T_CUSTOM_SIZE_AUTO ; 
 int /*<<< orphan*/  obs_data_set_default_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_data_set_default_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_data_set_default_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ss_defaults(obs_data_t *settings)
{
	obs_data_set_default_string(settings, S_TRANSITION, "fade");
	obs_data_set_default_int(settings, S_SLIDE_TIME, 8000);
	obs_data_set_default_int(settings, S_TR_SPEED, 700);
	obs_data_set_default_string(settings, S_CUSTOM_SIZE,
				    T_CUSTOM_SIZE_AUTO);
	obs_data_set_default_string(settings, S_BEHAVIOR,
				    S_BEHAVIOR_ALWAYS_PLAY);
	obs_data_set_default_string(settings, S_MODE, S_MODE_AUTO);
	obs_data_set_default_bool(settings, S_LOOP, true);
}