#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  refcount; int /*<<< orphan*/  minvif; scalar_t__ last_assert; } ;
struct TYPE_5__ {TYPE_1__ res; } ;
struct TYPE_6__ {TYPE_2__ mfc_un; int /*<<< orphan*/  free; } ;
struct mfc_cache {TYPE_3__ _c; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAXVIFS ; 
 scalar_t__ MFC_ASSERT_THRESH ; 
 int /*<<< orphan*/  ipmr_cache_free_rcu ; 
 scalar_t__ jiffies ; 
 struct mfc_cache* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrt_cachep ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct mfc_cache *ipmr_cache_alloc(void)
{
	struct mfc_cache *c = kmem_cache_zalloc(mrt_cachep, GFP_KERNEL);

	if (c) {
		c->_c.mfc_un.res.last_assert = jiffies - MFC_ASSERT_THRESH - 1;
		c->_c.mfc_un.res.minvif = MAXVIFS;
		c->_c.free = ipmr_cache_free_rcu;
		refcount_set(&c->_c.mfc_un.res.refcount, 1);
	}
	return c;
}