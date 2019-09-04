#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timespec {int dummy; } ;
struct ao_push_state {int final_chunk; int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup; int /*<<< orphan*/  buffer; scalar_t__ still_playing; scalar_t__ paused; } ;
struct ao {double buffer; TYPE_1__* driver; scalar_t__ samplerate; struct ao_push_state* api_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* drain ) (struct ao*) ;} ;

/* Variables and functions */
 int MPMIN (double,double) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*) ; 
 int /*<<< orphan*/  MP_WARN (struct ao*,char*) ; 
 scalar_t__ mp_audio_buffer_samples (int /*<<< orphan*/ ) ; 
 struct timespec mp_rel_time_to_timespec (double) ; 
 int /*<<< orphan*/  mp_sleep_us (int) ; 
 scalar_t__ pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset (struct ao*) ; 
 int /*<<< orphan*/  stub1 (struct ao*) ; 
 double unlocked_get_delay (struct ao*) ; 
 int /*<<< orphan*/  wakeup_playthread (struct ao*) ; 

__attribute__((used)) static void drain(struct ao *ao)
{
    struct ao_push_state *p = ao->api_priv;
    double maxbuffer = ao->buffer / (double)ao->samplerate + 1;

    MP_VERBOSE(ao, "draining...\n");

    pthread_mutex_lock(&p->lock);
    if (p->paused)
        goto done;

    p->final_chunk = true;
    wakeup_playthread(ao);

    // Wait until everything is done. Since the audio API (especially ALSA)
    // can't be trusted to do this right, and we're hard-blocking here, apply
    // an upper bound timeout.
    struct timespec until = mp_rel_time_to_timespec(maxbuffer);
    while (p->still_playing && mp_audio_buffer_samples(p->buffer) > 0) {
        if (pthread_cond_timedwait(&p->wakeup, &p->lock, &until)) {
            MP_WARN(ao, "Draining is taking too long, aborting.\n");
            goto done;
        }
    }

    if (ao->driver->drain) {
        ao->driver->drain(ao);
    } else {
        double time = unlocked_get_delay(ao);
        mp_sleep_us(MPMIN(time, maxbuffer) * 1e6);
    }

done:
    pthread_mutex_unlock(&p->lock);

    reset(ao);
}