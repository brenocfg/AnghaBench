#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct audio_cb_info {void* member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  audio_cb_mutex; int /*<<< orphan*/  audio_cb_list; } ;
typedef  TYPE_1__ obs_source_t ;
typedef  int /*<<< orphan*/  obs_source_audio_capture_t ;

/* Variables and functions */
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct audio_cb_info*) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void obs_source_add_audio_capture_callback(obs_source_t *source,
					   obs_source_audio_capture_t callback,
					   void *param)
{
	struct audio_cb_info info = {callback, param};

	if (!obs_source_valid(source, "obs_source_add_audio_capture_callback"))
		return;

	pthread_mutex_lock(&source->audio_cb_mutex);
	da_push_back(source->audio_cb_list, &info);
	pthread_mutex_unlock(&source->audio_cb_mutex);
}