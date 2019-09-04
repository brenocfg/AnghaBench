#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  dep_map; } ;
struct TYPE_12__ {TYPE_5__ base; TYPE_1__* ctx; } ;
struct TYPE_11__ {int /*<<< orphan*/  stamp; } ;

/* Variables and functions */
 int EDEADLK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WWAI (TYPE_1__*) ; 
 int WWL (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  WWU (TYPE_3__*) ; 
 int /*<<< orphan*/  _THIS_IP_ ; 
 int /*<<< orphan*/  mutex_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (TYPE_5__*) ; 
 int /*<<< orphan*/  mutex_release (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (TYPE_5__*) ; 
 TYPE_3__ o ; 
 TYPE_3__ o2 ; 
 TYPE_1__ t ; 
 TYPE_1__ t2 ; 

__attribute__((used)) static void ww_test_edeadlk_normal(void)
{
	int ret;

	mutex_lock(&o2.base);
	o2.ctx = &t2;
	mutex_release(&o2.base.dep_map, 1, _THIS_IP_);

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
	WWU(&o);

	WWL(&o2, &t);
}