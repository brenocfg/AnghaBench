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
 int /*<<< orphan*/  S_BEHAVIOR_STOP_RESTART ; 
 int /*<<< orphan*/  S_LOOP ; 
 int /*<<< orphan*/  S_NETWORK_CACHING ; 
 int /*<<< orphan*/  S_SHUFFLE ; 
 int /*<<< orphan*/  S_SUBTITLE_ENABLE ; 
 int /*<<< orphan*/  S_SUBTITLE_TRACK ; 
 int /*<<< orphan*/  S_TRACK ; 
 int /*<<< orphan*/  obs_data_set_default_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_data_set_default_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_data_set_default_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlcs_defaults(obs_data_t *settings)
{
	obs_data_set_default_bool(settings, S_LOOP, true);
	obs_data_set_default_bool(settings, S_SHUFFLE, false);
	obs_data_set_default_string(settings, S_BEHAVIOR,
				    S_BEHAVIOR_STOP_RESTART);
	obs_data_set_default_int(settings, S_NETWORK_CACHING, 400);
	obs_data_set_default_int(settings, S_TRACK, 1);
	obs_data_set_default_bool(settings, S_SUBTITLE_ENABLE, false);
	obs_data_set_default_int(settings, S_SUBTITLE_TRACK, 1);
}