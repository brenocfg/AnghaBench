#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; scalar_t__ audio_mix; } ;
struct obs_source {float user_volume; float volume; float balance; int audio_active; int deinterlace_top_first; int audio_mixers; int /*<<< orphan*/  private_settings; TYPE_2__* control; TYPE_1__ info; int /*<<< orphan*/  async_mutex; int /*<<< orphan*/  audio_mutex; int /*<<< orphan*/  audio_cb_mutex; int /*<<< orphan*/  audio_actions_mutex; int /*<<< orphan*/  audio_buf_mutex; int /*<<< orphan*/  filter_mutex; scalar_t__ sync_offset; } ;
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
typedef  int /*<<< orphan*/  obs_weak_source_t ;
struct TYPE_4__ {struct obs_source* source; } ;

/* Variables and functions */
 scalar_t__ OBS_SOURCE_TYPE_TRANSITION ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_RECURSIVE ; 
 int /*<<< orphan*/  allocate_audio_mix_buffer (struct obs_source*) ; 
 int /*<<< orphan*/  allocate_audio_output_buffer (struct obs_source*) ; 
 TYPE_2__* bzalloc (int) ; 
 scalar_t__ is_audio_source (struct obs_source*) ; 
 scalar_t__ is_composite_source (struct obs_source*) ; 
 int /*<<< orphan*/  obs_data_create () ; 
 int /*<<< orphan*/  obs_transition_init (struct obs_source*) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init_value (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool obs_source_init(struct obs_source *source)
{
	pthread_mutexattr_t attr;

	source->user_volume = 1.0f;
	source->volume = 1.0f;
	source->sync_offset = 0;
	source->balance = 0.5f;
	source->audio_active = true;
	pthread_mutex_init_value(&source->filter_mutex);
	pthread_mutex_init_value(&source->async_mutex);
	pthread_mutex_init_value(&source->audio_mutex);
	pthread_mutex_init_value(&source->audio_buf_mutex);
	pthread_mutex_init_value(&source->audio_cb_mutex);

	if (pthread_mutexattr_init(&attr) != 0)
		return false;
	if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) != 0)
		return false;
	if (pthread_mutex_init(&source->filter_mutex, &attr) != 0)
		return false;
	if (pthread_mutex_init(&source->audio_buf_mutex, NULL) != 0)
		return false;
	if (pthread_mutex_init(&source->audio_actions_mutex, NULL) != 0)
		return false;
	if (pthread_mutex_init(&source->audio_cb_mutex, NULL) != 0)
		return false;
	if (pthread_mutex_init(&source->audio_mutex, NULL) != 0)
		return false;
	if (pthread_mutex_init(&source->async_mutex, NULL) != 0)
		return false;

	if (is_audio_source(source) || is_composite_source(source))
		allocate_audio_output_buffer(source);
	if (source->info.audio_mix)
		allocate_audio_mix_buffer(source);

	if (source->info.type == OBS_SOURCE_TYPE_TRANSITION) {
		if (!obs_transition_init(source))
			return false;
	}

	source->control = bzalloc(sizeof(obs_weak_source_t));
	source->deinterlace_top_first = true;
	source->control->source = source;
	source->audio_mixers = 0xFF;

	source->private_settings = obs_data_create();
	return true;
}