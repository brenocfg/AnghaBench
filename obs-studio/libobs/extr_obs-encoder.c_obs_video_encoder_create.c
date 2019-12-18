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
typedef  int /*<<< orphan*/  obs_encoder_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_ENCODER_VIDEO ; 
 int /*<<< orphan*/ * create_encoder (char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

obs_encoder_t *obs_video_encoder_create(const char *id, const char *name,
					obs_data_t *settings,
					obs_data_t *hotkey_data)
{
	if (!name || !id)
		return NULL;
	return create_encoder(id, OBS_ENCODER_VIDEO, name, settings, 0,
			      hotkey_data);
}