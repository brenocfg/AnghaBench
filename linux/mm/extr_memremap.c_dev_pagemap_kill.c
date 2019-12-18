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
struct dev_pagemap {int /*<<< orphan*/  ref; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* kill ) (struct dev_pagemap*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  percpu_ref_kill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dev_pagemap*) ; 

__attribute__((used)) static void dev_pagemap_kill(struct dev_pagemap *pgmap)
{
	if (pgmap->ops && pgmap->ops->kill)
		pgmap->ops->kill(pgmap);
	else
		percpu_ref_kill(pgmap->ref);
}