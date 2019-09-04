#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dsa_switch_tree {TYPE_2__* cpu_dp; struct dsa_switch** ds; TYPE_1__* pd; } ;
struct dsa_switch {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  master; } ;
struct TYPE_3__ {int nr_chips; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_master_teardown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_switch_destroy (struct dsa_switch*) ; 

__attribute__((used)) static void dsa_remove_dst(struct dsa_switch_tree *dst)
{
	int i;

	dsa_master_teardown(dst->cpu_dp->master);

	for (i = 0; i < dst->pd->nr_chips; i++) {
		struct dsa_switch *ds = dst->ds[i];

		if (ds)
			dsa_switch_destroy(ds);
	}

	dev_put(dst->cpu_dp->master);
}