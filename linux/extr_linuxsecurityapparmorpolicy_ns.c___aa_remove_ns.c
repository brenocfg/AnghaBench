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
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct aa_ns {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_put_ns (struct aa_ns*) ; 
 int /*<<< orphan*/  destroy_ns (struct aa_ns*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 

void __aa_remove_ns(struct aa_ns *ns)
{
	/* remove ns from namespace list */
	list_del_rcu(&ns->base.list);
	destroy_ns(ns);
	aa_put_ns(ns);
}