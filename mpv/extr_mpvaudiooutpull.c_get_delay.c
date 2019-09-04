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
struct ao_pull_state {int /*<<< orphan*/ * buffers; int /*<<< orphan*/  end_time_us; } ;
struct ao {scalar_t__ bps; struct ao_pull_state* api_priv; } ;
typedef  double int64_t ;

/* Variables and functions */
 double MPMAX (int /*<<< orphan*/ ,double) ; 
 double atomic_load (int /*<<< orphan*/ *) ; 
 double mp_ring_buffered (int /*<<< orphan*/ ) ; 
 double mp_time_us () ; 

__attribute__((used)) static double get_delay(struct ao *ao)
{
    struct ao_pull_state *p = ao->api_priv;

    int64_t end = atomic_load(&p->end_time_us);
    int64_t now = mp_time_us();
    double driver_delay = MPMAX(0, (end - now) / (1000.0 * 1000.0));
    return mp_ring_buffered(p->buffers[0]) / (double)ao->bps + driver_delay;
}