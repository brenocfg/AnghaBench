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
struct ao_pull_state {int /*<<< orphan*/  underflow; int /*<<< orphan*/  draining; int /*<<< orphan*/  state; int /*<<< orphan*/ * buffers; } ;
struct ao {int sstride; int num_planes; TYPE_1__* driver; int /*<<< orphan*/  stream_silence; struct ao_pull_state* api_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (struct ao*) ;} ;

/* Variables and functions */
 int AOPLAY_FINAL_CHUNK ; 
 int /*<<< orphan*/  AO_STATE_PLAY ; 
 int /*<<< orphan*/  IS_PLAYING (int) ; 
 int MPMIN (int,int) ; 
 int /*<<< orphan*/  MP_WARN (struct ao*,char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int atomic_fetch_and (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int get_space (struct ao*) ; 
 int mp_ring_write (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  set_state (struct ao*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ao*) ; 

__attribute__((used)) static int play(struct ao *ao, void **data, int samples, int flags)
{
    struct ao_pull_state *p = ao->api_priv;

    int write_samples = get_space(ao);
    write_samples = MPMIN(write_samples, samples);

    // Write starting from the last plane - this way, the first plane will
    // always contain the minimum amount of data readable across all planes
    // (assumes the reader starts with the first plane).
    int write_bytes = write_samples * ao->sstride;
    for (int n = ao->num_planes - 1; n >= 0; n--) {
        int r = mp_ring_write(p->buffers[n], data[n], write_bytes);
        assert(r == write_bytes);
    }

    int state = atomic_load(&p->state);
    if (!IS_PLAYING(state)) {
        atomic_store(&p->draining, false);
        atomic_store(&p->underflow, 0);
        set_state(ao, AO_STATE_PLAY);
        if (!ao->stream_silence)
            ao->driver->resume(ao);
    }

    bool draining = write_samples == samples && (flags & AOPLAY_FINAL_CHUNK);
    atomic_store(&p->draining, draining);

    int underflow = atomic_fetch_and(&p->underflow, 0);
    if (underflow)
        MP_WARN(ao, "Audio underflow by %d samples.\n", underflow);

    return write_samples;
}