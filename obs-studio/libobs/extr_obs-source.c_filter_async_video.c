#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct obs_source_frame {int dummy; } ;
struct TYPE_7__ {scalar_t__ data; } ;
struct TYPE_6__ {struct obs_source_frame* (* filter_video ) (scalar_t__,struct obs_source_frame*) ;} ;
struct obs_source {TYPE_2__ context; TYPE_1__ info; int /*<<< orphan*/  enabled; } ;
struct TYPE_8__ {size_t num; struct obs_source** array; } ;
struct TYPE_9__ {int /*<<< orphan*/  filter_mutex; TYPE_3__ filters; } ;
typedef  TYPE_4__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 struct obs_source_frame* stub1 (scalar_t__,struct obs_source_frame*) ; 

struct obs_source_frame *filter_async_video(obs_source_t *source,
					    struct obs_source_frame *in)
{
	size_t i;

	pthread_mutex_lock(&source->filter_mutex);

	for (i = source->filters.num; i > 0; i--) {
		struct obs_source *filter = source->filters.array[i - 1];

		if (!filter->enabled)
			continue;

		if (filter->context.data && filter->info.filter_video) {
			in = filter->info.filter_video(filter->context.data,
						       in);
			if (!in)
				break;
		}
	}

	pthread_mutex_unlock(&source->filter_mutex);

	return in;
}