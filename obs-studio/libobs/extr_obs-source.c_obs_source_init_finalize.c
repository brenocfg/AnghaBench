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
struct obs_source {int /*<<< orphan*/  context; struct obs_source* next_audio_source; struct obs_source** prev_next_audio_source; } ;
struct TYPE_3__ {int /*<<< orphan*/  first_source; int /*<<< orphan*/  sources_mutex; int /*<<< orphan*/  audio_sources_mutex; struct obs_source* first_audio_source; } ;
struct TYPE_4__ {TYPE_1__ data; } ;

/* Variables and functions */
 scalar_t__ is_audio_source (struct obs_source*) ; 
 TYPE_2__* obs ; 
 int /*<<< orphan*/  obs_context_data_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void obs_source_init_finalize(struct obs_source *source)
{
	if (is_audio_source(source)) {
		pthread_mutex_lock(&obs->data.audio_sources_mutex);

		source->next_audio_source = obs->data.first_audio_source;
		source->prev_next_audio_source = &obs->data.first_audio_source;
		if (obs->data.first_audio_source)
			obs->data.first_audio_source->prev_next_audio_source =
				&source->next_audio_source;
		obs->data.first_audio_source = source;

		pthread_mutex_unlock(&obs->data.audio_sources_mutex);
	}

	obs_context_data_insert(&source->context, &obs->data.sources_mutex,
				&obs->data.first_source);
}