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
 int /*<<< orphan*/  obs_data_set_default_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  obs_data_set_default_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  obs_data_set_default_string (int /*<<< orphan*/ *,char*,char*) ; 

void nvenc_defaults(obs_data_t *settings)
{
	obs_data_set_default_int(settings, "bitrate", 2500);
	obs_data_set_default_int(settings, "max_bitrate", 5000);
	obs_data_set_default_int(settings, "keyint_sec", 0);
	obs_data_set_default_int(settings, "cqp", 20);
	obs_data_set_default_string(settings, "rate_control", "CBR");
	obs_data_set_default_string(settings, "preset", "hq");
	obs_data_set_default_string(settings, "profile", "high");
	obs_data_set_default_bool(settings, "psycho_aq", true);
	obs_data_set_default_int(settings, "gpu", 0);
	obs_data_set_default_int(settings, "bf", 2);
}