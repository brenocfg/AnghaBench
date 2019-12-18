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
struct dyn_event_operations {int /*<<< orphan*/  list; int /*<<< orphan*/  match; int /*<<< orphan*/  free; int /*<<< orphan*/  is_busy; int /*<<< orphan*/  show; int /*<<< orphan*/  create; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dyn_event_ops_list ; 
 int /*<<< orphan*/  dyn_event_ops_mutex ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int dyn_event_register(struct dyn_event_operations *ops)
{
	if (!ops || !ops->create || !ops->show || !ops->is_busy ||
	    !ops->free || !ops->match)
		return -EINVAL;

	INIT_LIST_HEAD(&ops->list);
	mutex_lock(&dyn_event_ops_mutex);
	list_add_tail(&ops->list, &dyn_event_ops_list);
	mutex_unlock(&dyn_event_ops_mutex);
	return 0;
}