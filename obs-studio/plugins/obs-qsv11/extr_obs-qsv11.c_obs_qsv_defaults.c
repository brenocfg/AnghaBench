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

__attribute__((used)) static void obs_qsv_defaults(obs_data_t *settings)
{
	obs_data_set_default_string(settings, "target_usage", "balanced");
	obs_data_set_default_int(settings, "bitrate", 2500);
	obs_data_set_default_int(settings, "max_bitrate", 3000);
	obs_data_set_default_string(settings, "profile", "high");
	obs_data_set_default_int(settings, "async_depth", 4);
	obs_data_set_default_string(settings, "rate_control", "CBR");

	obs_data_set_default_int(settings, "accuracy", 1000);
	obs_data_set_default_int(settings, "convergence", 1);
	obs_data_set_default_int(settings, "qpi", 23);
	obs_data_set_default_int(settings, "qpp", 23);
	obs_data_set_default_int(settings, "qpb", 23);
	obs_data_set_default_int(settings, "icq_quality", 23);
	obs_data_set_default_int(settings, "la_depth", 15);

	obs_data_set_default_int(settings, "keyint_sec", 3);
	obs_data_set_default_int(settings, "bframes", 3);
	obs_data_set_default_bool(settings, "mbbrc", true);
}