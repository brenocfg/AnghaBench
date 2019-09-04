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
struct vringh {unsigned int last_avail_idx; } ;

/* Variables and functions */

void vringh_abandon_kern(struct vringh *vrh, unsigned int num)
{
	/* We only update vring_avail_event(vr) when we want to be notified,
	 * so we haven't changed that yet. */
	vrh->last_avail_idx -= num;
}