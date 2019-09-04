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
struct ao_pull_state {int /*<<< orphan*/ * buffers; int /*<<< orphan*/  draining; int /*<<< orphan*/  state; } ;
struct ao {scalar_t__ bps; struct ao_pull_state* api_priv; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ IS_PLAYING (int) ; 
 int atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_eof (struct ao*) ; 
 double mp_ring_buffered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_sleep_us (int) ; 
 scalar_t__ mp_time_us () ; 
 int /*<<< orphan*/  reset (struct ao*) ; 

__attribute__((used)) static void drain(struct ao *ao)
{
    struct ao_pull_state *p = ao->api_priv;
    int state = atomic_load(&p->state);
    if (IS_PLAYING(state)) {
        atomic_store(&p->draining, true);
        // Wait for lower bound.
        mp_sleep_us(mp_ring_buffered(p->buffers[0]) / (double)ao->bps * 1e6);
        // And then poll for actual end. (Unfortunately, this code considers
        // audio APIs which do not want you to use mutexes in the audio
        // callback, and an extra semaphore would require slightly more effort.)
        // Limit to arbitrary ~250ms max. waiting for robustness.
        int64_t max = mp_time_us() + 250000;
        while (mp_time_us() < max && !get_eof(ao))
            mp_sleep_us(1);
    }
    reset(ao);
}