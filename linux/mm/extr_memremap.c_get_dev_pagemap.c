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
struct TYPE_2__ {scalar_t__ start; scalar_t__ end; } ;
struct dev_pagemap {int /*<<< orphan*/  ref; TYPE_1__ res; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 scalar_t__ PFN_PHYS (unsigned long) ; 
 int /*<<< orphan*/  PHYS_PFN (scalar_t__) ; 
 int /*<<< orphan*/  percpu_ref_tryget_live (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgmap_array ; 
 int /*<<< orphan*/  put_dev_pagemap (struct dev_pagemap*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct dev_pagemap* xa_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct dev_pagemap *get_dev_pagemap(unsigned long pfn,
		struct dev_pagemap *pgmap)
{
	resource_size_t phys = PFN_PHYS(pfn);

	/*
	 * In the cached case we're already holding a live reference.
	 */
	if (pgmap) {
		if (phys >= pgmap->res.start && phys <= pgmap->res.end)
			return pgmap;
		put_dev_pagemap(pgmap);
	}

	/* fall back to slow path lookup */
	rcu_read_lock();
	pgmap = xa_load(&pgmap_array, PHYS_PFN(phys));
	if (pgmap && !percpu_ref_tryget_live(pgmap->ref))
		pgmap = NULL;
	rcu_read_unlock();

	return pgmap;
}