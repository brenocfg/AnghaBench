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
struct ao_pull_state {int /*<<< orphan*/ * buffers; } ;
struct ao {struct ao_pull_state* api_priv; } ;

/* Variables and functions */
 scalar_t__ mp_ring_buffered (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool get_eof(struct ao *ao)
{
    struct ao_pull_state *p = ao->api_priv;
    // For simplicity, ignore the latency. Otherwise, we would have to run an
    // extra thread to time it.
    return mp_ring_buffered(p->buffers[0]) == 0;
}