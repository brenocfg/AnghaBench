#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct audio_data {int dummy; } ;
struct audio_cb_info {int /*<<< orphan*/  param; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,TYPE_2__*,struct audio_data const*,int) ;} ;
struct TYPE_5__ {size_t num; struct audio_cb_info* array; } ;
struct TYPE_6__ {int /*<<< orphan*/  audio_cb_mutex; TYPE_1__ audio_cb_list; } ;
typedef  TYPE_2__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,struct audio_data const*,int) ; 

__attribute__((used)) static void source_signal_audio_data(obs_source_t *source,
				     const struct audio_data *in, bool muted)
{
	pthread_mutex_lock(&source->audio_cb_mutex);

	for (size_t i = source->audio_cb_list.num; i > 0; i--) {
		struct audio_cb_info info = source->audio_cb_list.array[i - 1];
		info.callback(info.param, source, in, muted);
	}

	pthread_mutex_unlock(&source->audio_cb_mutex);
}