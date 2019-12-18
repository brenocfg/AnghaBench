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
struct ao_pull_state {int /*<<< orphan*/  end_time_us; int /*<<< orphan*/ * buffers; } ;
struct ao {int num_planes; TYPE_1__* driver; int /*<<< orphan*/  stream_silence; struct ao_pull_state* api_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct ao*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AO_STATE_NONE ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_ring_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_state (struct ao*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ao*) ; 

__attribute__((used)) static void reset(struct ao *ao)
{
    struct ao_pull_state *p = ao->api_priv;
    if (!ao->stream_silence && ao->driver->reset)
        ao->driver->reset(ao); // assumes the audio callback thread is stopped
    set_state(ao, AO_STATE_NONE);
    for (int n = 0; n < ao->num_planes; n++)
        mp_ring_reset(p->buffers[n]);
    atomic_store(&p->end_time_us, 0);
}