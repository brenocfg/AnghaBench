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
struct TYPE_2__ {void* ctx; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WWAI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nest_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ o ; 
 int /*<<< orphan*/  t ; 

__attribute__((used)) static void ww_test_normal(void)
{
	int ret;

	WWAI(&t);

	/*
	 * None of the ww_mutex codepaths should be taken in the 'normal'
	 * mutex calls. The easiest way to verify this is by using the
	 * normal mutex calls, and making sure o.ctx is unmodified.
	 */

	/* mutex_lock (and indirectly, mutex_lock_nested) */
	o.ctx = (void *)~0UL;
	mutex_lock(&o.base);
	mutex_unlock(&o.base);
	WARN_ON(o.ctx != (void *)~0UL);

	/* mutex_lock_interruptible (and *_nested) */
	o.ctx = (void *)~0UL;
	ret = mutex_lock_interruptible(&o.base);
	if (!ret)
		mutex_unlock(&o.base);
	else
		WARN_ON(1);
	WARN_ON(o.ctx != (void *)~0UL);

	/* mutex_lock_killable (and *_nested) */
	o.ctx = (void *)~0UL;
	ret = mutex_lock_killable(&o.base);
	if (!ret)
		mutex_unlock(&o.base);
	else
		WARN_ON(1);
	WARN_ON(o.ctx != (void *)~0UL);

	/* trylock, succeeding */
	o.ctx = (void *)~0UL;
	ret = mutex_trylock(&o.base);
	WARN_ON(!ret);
	if (ret)
		mutex_unlock(&o.base);
	else
		WARN_ON(1);
	WARN_ON(o.ctx != (void *)~0UL);

	/* trylock, failing */
	o.ctx = (void *)~0UL;
	mutex_lock(&o.base);
	ret = mutex_trylock(&o.base);
	WARN_ON(ret);
	mutex_unlock(&o.base);
	WARN_ON(o.ctx != (void *)~0UL);

	/* nest_lock */
	o.ctx = (void *)~0UL;
	mutex_lock_nest_lock(&o.base, &t);
	mutex_unlock(&o.base);
	WARN_ON(o.ctx != (void *)~0UL);
}