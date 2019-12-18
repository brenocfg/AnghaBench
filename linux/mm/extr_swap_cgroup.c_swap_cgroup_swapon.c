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
struct swap_cgroup_ctrl {unsigned long length; int /*<<< orphan*/ * map; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SC_PER_PAGE ; 
 int /*<<< orphan*/  do_swap_account ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct swap_cgroup_ctrl* swap_cgroup_ctrl ; 
 int /*<<< orphan*/  swap_cgroup_mutex ; 
 scalar_t__ swap_cgroup_prepare (int) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vzalloc (unsigned long) ; 

int swap_cgroup_swapon(int type, unsigned long max_pages)
{
	void *array;
	unsigned long array_size;
	unsigned long length;
	struct swap_cgroup_ctrl *ctrl;

	if (!do_swap_account)
		return 0;

	length = DIV_ROUND_UP(max_pages, SC_PER_PAGE);
	array_size = length * sizeof(void *);

	array = vzalloc(array_size);
	if (!array)
		goto nomem;

	ctrl = &swap_cgroup_ctrl[type];
	mutex_lock(&swap_cgroup_mutex);
	ctrl->length = length;
	ctrl->map = array;
	spin_lock_init(&ctrl->lock);
	if (swap_cgroup_prepare(type)) {
		/* memory shortage */
		ctrl->map = NULL;
		ctrl->length = 0;
		mutex_unlock(&swap_cgroup_mutex);
		vfree(array);
		goto nomem;
	}
	mutex_unlock(&swap_cgroup_mutex);

	return 0;
nomem:
	pr_info("couldn't allocate enough memory for swap_cgroup\n");
	pr_info("swap_cgroup can be disabled by swapaccount=0 boot option\n");
	return -ENOMEM;
}