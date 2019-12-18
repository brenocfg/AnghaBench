#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  dep_map; } ;
struct TYPE_11__ {TYPE_1__* ctx; TYPE_6__ base; } ;
struct TYPE_10__ {int /*<<< orphan*/  stamp; } ;

/* Variables and functions */
 int EDEADLK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WWAI (TYPE_1__*) ; 
 int WWL (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  _THIS_IP_ ; 
 int /*<<< orphan*/  mutex_lock (TYPE_6__*) ; 
 int /*<<< orphan*/  mutex_release (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_4__ o ; 
 TYPE_4__ o2 ; 
 int /*<<< orphan*/  o3 ; 
 TYPE_1__ t ; 
 TYPE_1__ t2 ; 
 int /*<<< orphan*/  ww_mutex_lock_slow (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void ww_test_edeadlk_acquire_more_slow(void)
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

	ww_mutex_lock_slow(&o3, &t);
}