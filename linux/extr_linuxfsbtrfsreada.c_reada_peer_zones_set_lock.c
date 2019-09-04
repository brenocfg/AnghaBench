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
struct reada_zone {unsigned long end; int ndevs; scalar_t__ device; int locked; TYPE_1__** devs; } ;
struct TYPE_2__ {int /*<<< orphan*/  reada_zones; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 struct reada_zone* radix_tree_lookup (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void reada_peer_zones_set_lock(struct reada_zone *zone, int lock)
{
	int i;
	unsigned long index = zone->end >> PAGE_SHIFT;

	for (i = 0; i < zone->ndevs; ++i) {
		struct reada_zone *peer;
		peer = radix_tree_lookup(&zone->devs[i]->reada_zones, index);
		if (peer && peer->device != zone->device)
			peer->locked = lock;
	}
}