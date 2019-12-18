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
struct rtmp_common {int dummy; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/  initialize_output (struct rtmp_common*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * open_services_file () ; 

__attribute__((used)) static void rtmp_common_apply_settings(void *data, obs_data_t *video_settings,
				       obs_data_t *audio_settings)
{
	struct rtmp_common *service = data;
	json_t *root = open_services_file();

	if (root) {
		initialize_output(service, root, video_settings,
				  audio_settings);
		json_decref(root);
	}
}