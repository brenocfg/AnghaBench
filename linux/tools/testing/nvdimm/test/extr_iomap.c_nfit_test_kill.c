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
struct dev_pagemap {int /*<<< orphan*/  ref; int /*<<< orphan*/  done; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cleanup ) (struct dev_pagemap*) ;int /*<<< orphan*/  (* kill ) (struct dev_pagemap*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  percpu_ref_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_ref_kill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dev_pagemap*) ; 
 int /*<<< orphan*/  stub2 (struct dev_pagemap*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfit_test_kill(void *_pgmap)
{
	struct dev_pagemap *pgmap = _pgmap;

	WARN_ON(!pgmap || !pgmap->ref);

	if (pgmap->ops && pgmap->ops->kill)
		pgmap->ops->kill(pgmap);
	else
		percpu_ref_kill(pgmap->ref);

	if (pgmap->ops && pgmap->ops->cleanup) {
		pgmap->ops->cleanup(pgmap);
	} else {
		wait_for_completion(&pgmap->done);
		percpu_ref_exit(pgmap->ref);
	}
}