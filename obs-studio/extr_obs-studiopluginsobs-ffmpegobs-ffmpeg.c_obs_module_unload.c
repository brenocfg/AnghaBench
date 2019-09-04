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
struct TYPE_4__ {size_t num; int /*<<< orphan*/ * array; } ;

/* Variables and functions */
 TYPE_1__ active_log_contexts ; 
 int /*<<< orphan*/  av_log_default_callback ; 
 int /*<<< orphan*/  av_log_set_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 TYPE_1__ cached_log_contexts ; 
 int /*<<< orphan*/  da_free (TYPE_1__) ; 

void obs_module_unload(void)
{
	av_log_set_callback(av_log_default_callback);

#ifdef _WIN32
	pthread_mutex_destroy(&log_contexts_mutex);
#endif

	for (size_t i = 0; i < active_log_contexts.num; i++) {
		bfree(active_log_contexts.array[i]);
	}
	for (size_t i = 0; i < cached_log_contexts.num; i++) {
		bfree(cached_log_contexts.array[i]);
	}

	da_free(active_log_contexts);
	da_free(cached_log_contexts);

#ifdef _WIN32
	jim_nvenc_unload();
#endif
}