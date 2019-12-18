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
struct obs_source_frame {int format; int refs; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  full_range; } ;
struct TYPE_4__ {size_t num; struct async_frame* array; } ;
struct TYPE_3__ {scalar_t__ num; } ;
struct obs_source {int async_cache_format; int /*<<< orphan*/  async_mutex; TYPE_2__ async_cache; int /*<<< orphan*/  async_cache_full_range; int /*<<< orphan*/  async_cache_height; int /*<<< orphan*/  async_cache_width; scalar_t__ last_frame_ts; TYPE_1__ async_frames; } ;
struct async_frame {int used; scalar_t__ unused_count; struct obs_source_frame* frame; } ;
typedef  enum video_format { ____Placeholder_video_format } video_format ;

/* Variables and functions */
 scalar_t__ MAX_ASYNC_FRAMES ; 
 scalar_t__ async_texture_changed (struct obs_source*,struct obs_source_frame const*) ; 
 int /*<<< orphan*/  clean_cache (struct obs_source*) ; 
 int /*<<< orphan*/  copy_frame_data (struct obs_source_frame*,struct obs_source_frame const*) ; 
 int /*<<< orphan*/  da_push_back (TYPE_2__,struct async_frame*) ; 
 int /*<<< orphan*/  free_async_cache (struct obs_source*) ; 
 struct obs_source_frame* obs_source_frame_create (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_atomic_inc_long (int*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct obs_source_frame *
cache_video(struct obs_source *source, const struct obs_source_frame *frame)
{
	struct obs_source_frame *new_frame = NULL;

	pthread_mutex_lock(&source->async_mutex);

	if (source->async_frames.num >= MAX_ASYNC_FRAMES) {
		free_async_cache(source);
		source->last_frame_ts = 0;
		pthread_mutex_unlock(&source->async_mutex);
		return NULL;
	}

	if (async_texture_changed(source, frame)) {
		free_async_cache(source);
		source->async_cache_width = frame->width;
		source->async_cache_height = frame->height;
	}

	const enum video_format format = frame->format;
	source->async_cache_format = format;
	source->async_cache_full_range = frame->full_range;

	for (size_t i = 0; i < source->async_cache.num; i++) {
		struct async_frame *af = &source->async_cache.array[i];
		if (!af->used) {
			new_frame = af->frame;
			new_frame->format = format;
			af->used = true;
			af->unused_count = 0;
			break;
		}
	}

	clean_cache(source);

	if (!new_frame) {
		struct async_frame new_af;

		new_frame = obs_source_frame_create(format, frame->width,
						    frame->height);
		new_af.frame = new_frame;
		new_af.used = true;
		new_af.unused_count = 0;
		new_frame->refs = 1;

		da_push_back(source->async_cache, &new_af);
	}

	os_atomic_inc_long(&new_frame->refs);

	pthread_mutex_unlock(&source->async_mutex);

	copy_frame_data(new_frame, frame);

	return new_frame;
}