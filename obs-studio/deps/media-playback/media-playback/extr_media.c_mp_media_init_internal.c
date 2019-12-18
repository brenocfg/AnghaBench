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
struct mp_media_info {int /*<<< orphan*/  hardware_decoding; scalar_t__ format; scalar_t__ path; } ;
struct TYPE_4__ {int thread_valid; int /*<<< orphan*/  thread; int /*<<< orphan*/  hw; int /*<<< orphan*/ * format_name; int /*<<< orphan*/ * path; int /*<<< orphan*/  sem; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ mp_media_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * bstrdup (scalar_t__) ; 
 int /*<<< orphan*/  mp_media_thread_start ; 
 scalar_t__ os_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool mp_media_init_internal(mp_media_t *m,
					  const struct mp_media_info *info)
{
	if (pthread_mutex_init(&m->mutex, NULL) != 0) {
		blog(LOG_WARNING, "MP: Failed to init mutex");
		return false;
	}
	if (os_sem_init(&m->sem, 0) != 0) {
		blog(LOG_WARNING, "MP: Failed to init semaphore");
		return false;
	}

	m->path = info->path ? bstrdup(info->path) : NULL;
	m->format_name = info->format ? bstrdup(info->format) : NULL;
	m->hw = info->hardware_decoding;

	if (pthread_create(&m->thread, NULL, mp_media_thread_start, m) != 0) {
		blog(LOG_WARNING, "MP: Could not create media thread");
		return false;
	}

	m->thread_valid = true;
	return true;
}