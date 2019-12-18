#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ addr; } ;
struct trace_event_finder {int ntevs; TYPE_3__* tevs; TYPE_1__ pf; } ;
struct TYPE_5__ {scalar_t__ address; } ;
struct TYPE_6__ {TYPE_2__ point; } ;

/* Variables and functions */

__attribute__((used)) static bool trace_event_finder_overlap(struct trace_event_finder *tf)
{
	int i;

	for (i = 0; i < tf->ntevs; i++) {
		if (tf->pf.addr == tf->tevs[i].point.address)
			return true;
	}
	return false;
}