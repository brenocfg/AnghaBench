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
struct ao_pull_state {int /*<<< orphan*/  state; int /*<<< orphan*/ * buffers; } ;
struct ao {int num_planes; int buffer; int sstride; TYPE_1__* driver; scalar_t__ stream_silence; struct ao_pull_state* api_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (struct ao*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AO_STATE_NONE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/  (*) (struct ao*)) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_ring_new (struct ao*,int) ; 
 int /*<<< orphan*/  stub1 (struct ao*) ; 

__attribute__((used)) static int init(struct ao *ao)
{
    struct ao_pull_state *p = ao->api_priv;
    for (int n = 0; n < ao->num_planes; n++)
        p->buffers[n] = mp_ring_new(ao, ao->buffer * ao->sstride);
    atomic_store(&p->state, AO_STATE_NONE);
    assert(ao->driver->resume);

    if (ao->stream_silence)
        ao->driver->resume(ao);

    return 0;
}