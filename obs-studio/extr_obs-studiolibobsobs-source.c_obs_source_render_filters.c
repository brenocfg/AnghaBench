#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__** array; } ;
struct TYPE_8__ {int rendering_filter; int /*<<< orphan*/  filter_mutex; TYPE_1__ filters; } ;
typedef  TYPE_2__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_source_addref (TYPE_2__*) ; 
 int /*<<< orphan*/  obs_source_release (TYPE_2__*) ; 
 int /*<<< orphan*/  obs_source_video_render (TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void obs_source_render_filters(obs_source_t *source)
{
	obs_source_t *first_filter;

	pthread_mutex_lock(&source->filter_mutex);
	first_filter = source->filters.array[0];
	obs_source_addref(first_filter);
	pthread_mutex_unlock(&source->filter_mutex);

	source->rendering_filter = true;
	obs_source_video_render(first_filter);
	source->rendering_filter = false;

	obs_source_release(first_filter);
}