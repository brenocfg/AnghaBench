#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  dep_map; } ;
struct TYPE_13__ {int /*<<< orphan*/  stamp; } ;
struct TYPE_12__ {TYPE_7__ base; TYPE_2__* ctx; } ;

/* Variables and functions */
 int EDEADLK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WWAI (TYPE_2__*) ; 
 int WWL (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  _THIS_IP_ ; 
 int /*<<< orphan*/  mutex_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (TYPE_7__*) ; 
 int /*<<< orphan*/  mutex_release (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (TYPE_7__*) ; 
 TYPE_1__ o ; 
 TYPE_1__ o2 ; 
 TYPE_2__ t ; 
 TYPE_2__ t2 ; 
 int /*<<< orphan*/  ww_mutex_lock_slow (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void ww_test_edeadlk_no_unlock_slow(void)
{
	int ret;

	mutex_lock(&o2.base);
	mutex_release(&o2.base.dep_map, 1, _THIS_IP_);
	o2.ctx = &t2;

	WWAI(&t);
	t2 = t;
	t2.stamp--;

	ret = WWL(&o, &t);
	WARN_ON(ret);

	ret = WWL(&o2, &t);
	WARN_ON(ret != -EDEADLK);

	o2.ctx = NULL;
	mutex_acquire(&o2.base.dep_map, 0, 1, _THIS_IP_);
	mutex_unlock(&o2.base);

	ww_mutex_lock_slow(&o2, &t);
}