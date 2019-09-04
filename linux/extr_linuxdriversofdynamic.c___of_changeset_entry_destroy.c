#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct of_changeset_entry {scalar_t__ action; int /*<<< orphan*/  node; TYPE_2__* np; } ;
struct TYPE_6__ {int /*<<< orphan*/  kref; } ;
struct TYPE_7__ {TYPE_1__ kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  OF_OVERLAY ; 
 int /*<<< orphan*/  OF_OVERLAY_FREE_CSET ; 
 scalar_t__ OF_RECONFIG_ATTACH_NODE ; 
 int /*<<< orphan*/  kfree (struct of_changeset_entry*) ; 
 int kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ of_node_check_flag (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (TYPE_2__*) ; 
 int /*<<< orphan*/  of_node_set_flag (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,TYPE_2__*) ; 

__attribute__((used)) static void __of_changeset_entry_destroy(struct of_changeset_entry *ce)
{
	if (ce->action == OF_RECONFIG_ATTACH_NODE &&
	    of_node_check_flag(ce->np, OF_OVERLAY)) {
		if (kref_read(&ce->np->kobj.kref) > 1) {
			pr_err("ERROR: memory leak, expected refcount 1 instead of %d, of_node_get()/of_node_put() unbalanced - destroy cset entry: attach overlay node %pOF\n",
			       kref_read(&ce->np->kobj.kref), ce->np);
		} else {
			of_node_set_flag(ce->np, OF_OVERLAY_FREE_CSET);
		}
	}

	of_node_put(ce->np);
	list_del(&ce->node);
	kfree(ce);
}