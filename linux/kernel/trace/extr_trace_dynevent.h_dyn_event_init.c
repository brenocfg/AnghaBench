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
struct dyn_event_operations {int dummy; } ;
struct dyn_event {struct dyn_event_operations* ops; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline
int dyn_event_init(struct dyn_event *ev, struct dyn_event_operations *ops)
{
	if (!ev || !ops)
		return -EINVAL;

	INIT_LIST_HEAD(&ev->list);
	ev->ops = ops;
	return 0;
}