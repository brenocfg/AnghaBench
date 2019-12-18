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
struct TYPE_4__ {scalar_t__ expires; int /*<<< orphan*/  unresolved; } ;
struct TYPE_5__ {TYPE_1__ unres; } ;
struct TYPE_6__ {TYPE_2__ mfc_un; } ;
struct mfc_cache {TYPE_3__ _c; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HZ ; 
 scalar_t__ jiffies ; 
 struct mfc_cache* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrt_cachep ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mfc_cache *ipmr_cache_alloc_unres(void)
{
	struct mfc_cache *c = kmem_cache_zalloc(mrt_cachep, GFP_ATOMIC);

	if (c) {
		skb_queue_head_init(&c->_c.mfc_un.unres.unresolved);
		c->_c.mfc_un.unres.expires = jiffies + 10 * HZ;
	}
	return c;
}