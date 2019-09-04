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
struct select_data {scalar_t__ found; int /*<<< orphan*/  dispose; struct dentry* start; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  d_walk (struct dentry*,struct select_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  select_collect ; 
 int /*<<< orphan*/  shrink_dentry_list (int /*<<< orphan*/ *) ; 

void shrink_dcache_parent(struct dentry *parent)
{
	for (;;) {
		struct select_data data;

		INIT_LIST_HEAD(&data.dispose);
		data.start = parent;
		data.found = 0;

		d_walk(parent, &data, select_collect);

		if (!list_empty(&data.dispose)) {
			shrink_dentry_list(&data.dispose);
			continue;
		}

		cond_resched();
		if (!data.found)
			break;
	}
}