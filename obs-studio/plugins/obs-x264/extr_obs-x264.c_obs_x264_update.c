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
struct obs_x264 {int /*<<< orphan*/  params; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int update_settings (struct obs_x264*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  warn (char*,int) ; 
 int x264_encoder_reconfig (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool obs_x264_update(void *data, obs_data_t *settings)
{
	struct obs_x264 *obsx264 = data;
	bool success = update_settings(obsx264, settings, true);
	int ret;

	if (success) {
		ret = x264_encoder_reconfig(obsx264->context, &obsx264->params);
		if (ret != 0)
			warn("Failed to reconfigure: %d", ret);
		return ret == 0;
	}

	return false;
}