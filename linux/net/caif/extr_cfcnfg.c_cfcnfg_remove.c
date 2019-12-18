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
struct cfcnfg {int /*<<< orphan*/  ctrl; struct cfcnfg* mux; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfctrl_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cfcnfg*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void cfcnfg_remove(struct cfcnfg *cfg)
{
	might_sleep();
	if (cfg) {
		synchronize_rcu();

		kfree(cfg->mux);
		cfctrl_remove(cfg->ctrl);
		kfree(cfg);
	}
}