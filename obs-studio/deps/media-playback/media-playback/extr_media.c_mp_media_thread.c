#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int active; int reset; int kill; scalar_t__ has_audio; scalar_t__ has_video; int /*<<< orphan*/  mutex; int /*<<< orphan*/  sem; } ;
typedef  TYPE_1__ mp_media_t ;

/* Variables and functions */
 int /*<<< orphan*/  init_avformat (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_media_calc_next_ns (TYPE_1__*) ; 
 scalar_t__ mp_media_eof (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_media_next_audio (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_media_next_video (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mp_media_prepare_frames (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_media_reset (TYPE_1__*) ; 
 int mp_media_sleepto (TYPE_1__*) ; 
 scalar_t__ os_sem_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_set_thread_name (char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool mp_media_thread(mp_media_t *m)
{
	os_set_thread_name("mp_media_thread");

	if (!init_avformat(m)) {
		return false;
	}
	if (!mp_media_reset(m)) {
		return false;
	}

	for (;;) {
		bool reset, kill, is_active;
		bool timeout = false;

		pthread_mutex_lock(&m->mutex);
		is_active = m->active;
		pthread_mutex_unlock(&m->mutex);

		if (!is_active) {
			if (os_sem_wait(m->sem) < 0)
				return false;
		} else {
			timeout = mp_media_sleepto(m);
		}

		pthread_mutex_lock(&m->mutex);

		reset = m->reset;
		kill = m->kill;
		m->reset = false;
		m->kill = false;

		pthread_mutex_unlock(&m->mutex);

		if (kill) {
			break;
		}
		if (reset) {
			mp_media_reset(m);
			continue;
		}

		/* frames are ready */
		if (is_active && !timeout) {
			if (m->has_video)
				mp_media_next_video(m, false);
			if (m->has_audio)
				mp_media_next_audio(m);

			if (!mp_media_prepare_frames(m))
				return false;
			if (mp_media_eof(m))
				continue;

			mp_media_calc_next_ns(m);
		}
	}

	return true;
}