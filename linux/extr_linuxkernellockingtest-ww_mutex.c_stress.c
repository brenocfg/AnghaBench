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
struct ww_mutex {int dummy; } ;
struct stress {int nlocks; int /*<<< orphan*/  work; scalar_t__ timeout; struct ww_mutex* locks; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,void (*) (struct work_struct*)) ; 
 unsigned int STRESS_INORDER ; 
 unsigned int STRESS_ONE ; 
 unsigned int STRESS_REORDER ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct ww_mutex*) ; 
 struct stress* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct ww_mutex* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void stress_inorder_work (struct work_struct*) ; 
 void stress_one_work (struct work_struct*) ; 
 void stress_reorder_work (struct work_struct*) ; 
 int /*<<< orphan*/  wq ; 
 int /*<<< orphan*/  ww_class ; 
 int /*<<< orphan*/  ww_mutex_destroy (struct ww_mutex*) ; 
 int /*<<< orphan*/  ww_mutex_init (struct ww_mutex*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stress(int nlocks, int nthreads, unsigned int flags)
{
	struct ww_mutex *locks;
	int n;

	locks = kmalloc_array(nlocks, sizeof(*locks), GFP_KERNEL);
	if (!locks)
		return -ENOMEM;

	for (n = 0; n < nlocks; n++)
		ww_mutex_init(&locks[n], &ww_class);

	for (n = 0; nthreads; n++) {
		struct stress *stress;
		void (*fn)(struct work_struct *work);

		fn = NULL;
		switch (n & 3) {
		case 0:
			if (flags & STRESS_INORDER)
				fn = stress_inorder_work;
			break;
		case 1:
			if (flags & STRESS_REORDER)
				fn = stress_reorder_work;
			break;
		case 2:
			if (flags & STRESS_ONE)
				fn = stress_one_work;
			break;
		}

		if (!fn)
			continue;

		stress = kmalloc(sizeof(*stress), GFP_KERNEL);
		if (!stress)
			break;

		INIT_WORK(&stress->work, fn);
		stress->locks = locks;
		stress->nlocks = nlocks;
		stress->timeout = jiffies + 2*HZ;

		queue_work(wq, &stress->work);
		nthreads--;
	}

	flush_workqueue(wq);

	for (n = 0; n < nlocks; n++)
		ww_mutex_destroy(&locks[n]);
	kfree(locks);

	return 0;
}