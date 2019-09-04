#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  frame_ready; } ;
struct TYPE_7__ {int /*<<< orphan*/  frame_ready; } ;
struct TYPE_8__ {int looping; int active; int stopping; int /*<<< orphan*/  mutex; TYPE_1__ a; int /*<<< orphan*/  has_audio; TYPE_2__ v; int /*<<< orphan*/  has_video; } ;
typedef  TYPE_3__ mp_media_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_media_reset (TYPE_3__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool mp_media_eof(mp_media_t *m)
{
	bool v_ended = !m->has_video || !m->v.frame_ready;
	bool a_ended = !m->has_audio || !m->a.frame_ready;
	bool eof = v_ended && a_ended;

	if (eof) {
		bool looping;

		pthread_mutex_lock(&m->mutex);
		looping = m->looping;
		if (!looping) {
			m->active = false;
			m->stopping = true;
		}
		pthread_mutex_unlock(&m->mutex);

		mp_media_reset(m);
	}

	return eof;
}