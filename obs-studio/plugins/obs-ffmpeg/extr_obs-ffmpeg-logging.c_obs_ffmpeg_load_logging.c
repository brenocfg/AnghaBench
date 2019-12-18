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

/* Variables and functions */
 int /*<<< orphan*/  active_log_contexts ; 
 int /*<<< orphan*/  av_log_set_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cached_log_contexts ; 
 int /*<<< orphan*/  da_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffmpeg_log_callback ; 
 int /*<<< orphan*/  log_contexts_mutex ; 
 int logging_initialized ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void obs_ffmpeg_load_logging(void)
{
	da_init(active_log_contexts);
	da_init(cached_log_contexts);

	if (pthread_mutex_init(&log_contexts_mutex, NULL) == 0) {
		av_log_set_callback(ffmpeg_log_callback);
		logging_initialized = true;
	}
}