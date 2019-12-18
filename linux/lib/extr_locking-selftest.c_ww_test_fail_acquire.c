#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_9__ {int /*<<< orphan*/  stamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOCKS_WARN_ON (int) ; 
 int EALREADY ; 
 int EDEADLK ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WWAI (TYPE_1__*) ; 
 int WWL (TYPE_3__*,TYPE_1__*) ; 
 int WWT (TYPE_3__*) ; 
 int /*<<< orphan*/  WWU (TYPE_3__*) ; 
 TYPE_3__ o ; 
 TYPE_1__ t ; 
 TYPE_1__ t2 ; 

__attribute__((used)) static void ww_test_fail_acquire(void)
{
	int ret;

	WWAI(&t);
	t.stamp++;

	ret = WWL(&o, &t);

	if (WARN_ON(!o.ctx) ||
	    WARN_ON(ret))
		return;

	/* No lockdep test, pure API */
	ret = WWL(&o, &t);
	WARN_ON(ret != -EALREADY);

	ret = WWT(&o);
	WARN_ON(ret);

	t2 = t;
	t2.stamp++;
	ret = WWL(&o, &t2);
	WARN_ON(ret != -EDEADLK);
	WWU(&o);

	if (WWT(&o))
		WWU(&o);
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	else
		DEBUG_LOCKS_WARN_ON(1);
#endif
}