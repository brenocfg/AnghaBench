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
struct ao_push_state {int paused; int still_playing; int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer; } ;
struct ao {TYPE_1__* driver; struct ao_push_state* api_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct ao*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mp_audio_buffer_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ao*) ; 
 int /*<<< orphan*/  wakeup_playthread (struct ao*) ; 

__attribute__((used)) static void reset(struct ao *ao)
{
    struct ao_push_state *p = ao->api_priv;
    pthread_mutex_lock(&p->lock);
    if (ao->driver->reset)
        ao->driver->reset(ao);
    mp_audio_buffer_clear(p->buffer);
    p->paused = false;
    if (p->still_playing)
        wakeup_playthread(ao);
    p->still_playing = false;
    pthread_mutex_unlock(&p->lock);
}