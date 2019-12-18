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
struct dyn_event {int /*<<< orphan*/  list; int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dyn_event_list ; 
 int /*<<< orphan*/  event_mutex ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int dyn_event_add(struct dyn_event *ev)
{
	lockdep_assert_held(&event_mutex);

	if (!ev || !ev->ops)
		return -EINVAL;

	list_add_tail(&ev->list, &dyn_event_list);
	return 0;
}