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
struct ao {int num_planes; int sstride; struct ao_pull_state* api_priv; } ;

/* Variables and functions */
 int mp_ring_available (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_space(struct ao *ao)
{
    struct ao_pull_state *p = ao->api_priv;
    // Since the reader will read the last plane last, its free space is the
    // minimum free space across all planes.
    return mp_ring_available(p->buffers[ao->num_planes - 1]) / ao->sstride;
}